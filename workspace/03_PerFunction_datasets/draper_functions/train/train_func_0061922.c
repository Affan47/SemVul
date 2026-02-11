solos_param_show(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct atm_dev *atmdev = container_of(dev, struct atm_dev, class_dev);
	struct solos_card *card = atmdev->dev_data;
	struct solos_param prm;
	struct sk_buff *skb;
	struct pkt_hdr *header;
	int buflen;

	buflen = strlen(attr->attr.name) + 10;

	skb = alloc_skb(sizeof(*header) + buflen, GFP_KERNEL);
	if (!skb) {
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in solos_param_show()\n");
		return -ENOMEM;
	}

	header = (void *)skb_put(skb, sizeof(*header));

	buflen = snprintf((void *)&header[1], buflen - 1,
			  "L%05d\n%s\n", current->pid, attr->attr.name);
	skb_put(skb, buflen);

	header->size = cpu_to_le16(buflen);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	prm.pid = current->pid;
	prm.response = NULL;
	prm.port = SOLOS_CHAN(atmdev);

	spin_lock_irq(&card->param_queue_lock);
	list_add(&prm.list, &card->param_queue);
	spin_unlock_irq(&card->param_queue_lock);

	fpga_queue(card, prm.port, skb, NULL);

	wait_event_timeout(card->param_wq, prm.response, 5 * HZ);

	spin_lock_irq(&card->param_queue_lock);
	list_del(&prm.list);
	spin_unlock_irq(&card->param_queue_lock);

	if (!prm.response)
		return -EIO;

	buflen = prm.response->len;
	memcpy(buf, prm.response->data, buflen);
	kfree_skb(prm.response);

	return buflen;
}
