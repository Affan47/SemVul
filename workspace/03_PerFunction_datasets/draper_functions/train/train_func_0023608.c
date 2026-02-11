i2400m_rx_ctl(struct i2400m *i2400m, struct sk_buff *skb_rx,
		   const void *payload, size_t size)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_l3l4_hdr *l3l4_hdr = payload;
	unsigned msg_type;

	result = i2400m_msg_size_check(i2400m, l3l4_hdr, size);
	if (result < 0) {
		dev_err(dev, "HW BUG? device sent a bad message: %d\n",
			result);
		goto error_check;
	}
	msg_type = le16_to_cpu(l3l4_hdr->type);
	d_printf(1, dev, "%s 0x%04x: %zu bytes\n",
		 msg_type & I2400M_MT_REPORT_MASK ? "REPORT" : "CMD/SET/GET",
		 msg_type, size);
	d_dump(2, dev, l3l4_hdr, size);
	if (msg_type & I2400M_MT_REPORT_MASK) {


		i2400m_report_hook_queue(i2400m, skb_rx, l3l4_hdr, size);
		if (unlikely(i2400m->trace_msg_from_user))
			wimax_msg(&i2400m->wimax_dev, "echo",
				  l3l4_hdr, size, GFP_KERNEL);
		result = wimax_msg(&i2400m->wimax_dev, NULL, l3l4_hdr, size,
				   GFP_KERNEL);
		if (result < 0)
			dev_err(dev, "error sending report to userspace: %d\n",
				result);
	} else
		i2400m_rx_ctl_ack(i2400m, payload, size);
error_check:
	return;
}
