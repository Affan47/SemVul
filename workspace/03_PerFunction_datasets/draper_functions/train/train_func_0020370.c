store_protocols(struct device *device,
			       struct device_attribute *mattr,
			       const char *buf, size_t len)
{
	struct rc_dev *dev = to_rc_dev(device);
	struct rc_filter_attribute *fattr = to_rc_filter_attr(mattr);
	u64 *current_protocols;
	int (*change_protocol)(struct rc_dev *dev, u64 *rc_type);
	struct rc_scancode_filter *filter;
	int (*set_filter)(struct rc_dev *dev, struct rc_scancode_filter *filter);
	u64 old_protocols, new_protocols;
	ssize_t rc;


	if (!dev)
		return -EINVAL;

	if (fattr->type == RC_FILTER_NORMAL) {
		IR_dprintk(1, "Normal protocol change requested\n");
		current_protocols = &dev->enabled_protocols;
		change_protocol = dev->change_protocol;
		filter = &dev->scancode_filter;
		set_filter = dev->s_filter;
	} else {
		IR_dprintk(1, "Wakeup protocol change requested\n");
		current_protocols = &dev->enabled_wakeup_protocols;
		change_protocol = dev->change_wakeup_protocol;
		filter = &dev->scancode_wakeup_filter;
		set_filter = dev->s_wakeup_filter;
	}

	if (!change_protocol) {
		IR_dprintk(1, "Protocol switching not supported\n");
		return -EINVAL;
	}

	mutex_lock(&dev->lock);

	old_protocols = *current_protocols;
	new_protocols = old_protocols;
	rc = parse_protocol_change(&new_protocols, buf);
	if (rc < 0)
		goto out;

	rc = change_protocol(dev, &new_protocols);
	if (rc < 0) {
		IR_dprintk(1, "Error setting protocols to 0x%llx\n",
			   (long long)new_protocols);
		goto out;
	}

	if (new_protocols != old_protocols) {
		*current_protocols = new_protocols;
		IR_dprintk(1, "Protocols changed to 0x%llx\n",
			   (long long)new_protocols);
	}


	if (set_filter && filter->mask) {
		if (new_protocols)
			rc = set_filter(dev, filter);
		else
			rc = -1;

		if (rc < 0) {
			filter->data = 0;
			filter->mask = 0;
			set_filter(dev, filter);
		}
	}

	rc = len;

out:
	mutex_unlock(&dev->lock);
	return rc;
}
