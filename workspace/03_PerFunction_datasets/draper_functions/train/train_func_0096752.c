thermal_generate_netlink_event(struct thermal_zone_device *tz,
					enum events event)
{
	struct sk_buff *skb;
	struct nlattr *attr;
	struct thermal_genl_event *thermal_event;
	void *msg_header;
	int size;
	int result;
	static unsigned int thermal_event_seqnum;

	if (!tz)
		return -EINVAL;


	size = nla_total_size(sizeof(struct thermal_genl_event)) +
	       nla_total_size(0);

	skb = genlmsg_new(size, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;


	msg_header = genlmsg_put(skb, 0, thermal_event_seqnum++,
				 &thermal_event_genl_family, 0,
				 THERMAL_GENL_CMD_EVENT);
	if (!msg_header) {
		nlmsg_free(skb);
		return -ENOMEM;
	}


	attr = nla_reserve(skb, THERMAL_GENL_ATTR_EVENT,
			   sizeof(struct thermal_genl_event));

	if (!attr) {
		nlmsg_free(skb);
		return -EINVAL;
	}

	thermal_event = nla_data(attr);
	if (!thermal_event) {
		nlmsg_free(skb);
		return -EINVAL;
	}

	memset(thermal_event, 0, sizeof(struct thermal_genl_event));

	thermal_event->orig = tz->id;
	thermal_event->event = event;


	genlmsg_end(skb, msg_header);

	result = genlmsg_multicast(&thermal_event_genl_family, skb, 0,
				   0, GFP_ATOMIC);
	if (result)
		dev_err(&tz->device, "Failed to send netlink event:%d", result);

	return result;
}
