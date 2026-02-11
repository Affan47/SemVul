fc_host_post_vendor_event(struct Scsi_Host *shost, u32 event_number,
		u32 data_len, char * data_buf, u64 vendor_id)
{
	struct sk_buff *skb;
	struct nlmsghdr	*nlh;
	struct fc_nl_event *event;
	u32 len;
	int err;

	if (!scsi_nl_sock) {
		err = -ENOENT;
		goto send_vendor_fail;
	}

	len = FC_NL_MSGALIGN(sizeof(*event) + data_len);

	skb = nlmsg_new(len, GFP_KERNEL);
	if (!skb) {
		err = -ENOBUFS;
		goto send_vendor_fail;
	}

	nlh = nlmsg_put(skb, 0, 0, SCSI_TRANSPORT_MSG, len, 0);
	if (!nlh) {
		err = -ENOBUFS;
		goto send_vendor_fail_skb;
	}
	event = nlmsg_data(nlh);

	INIT_SCSI_NL_HDR(&event->snlh, SCSI_NL_TRANSPORT_FC,
				FC_NL_ASYNC_EVENT, len);
	event->seconds = get_seconds();
	event->vendor_id = vendor_id;
	event->host_no = shost->host_no;
	event->event_datalen = data_len;
	event->event_num = event_number;
	event->event_code = FCH_EVT_VENDOR_UNIQUE;
	memcpy(&event->event_data, data_buf, data_len);

	nlmsg_multicast(scsi_nl_sock, skb, 0, SCSI_NL_GRP_FC_EVENTS,
			GFP_KERNEL);
	return;

send_vendor_fail_skb:
	kfree_skb(skb);
send_vendor_fail:
	printk(KERN_WARNING
		"%s: Dropped Event : host %d vendor_unique - err %d\n",
		__func__, shost->host_no, err);
	return;
}
