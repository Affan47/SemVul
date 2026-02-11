popen(struct atm_vcc *vcc)
{
	struct solos_card *card = vcc->dev->dev_data;
	struct sk_buff *skb;
	struct pkt_hdr *header;

	if (vcc->qos.aal != ATM_AAL5) {
		dev_warn(&card->dev->dev, "Unsupported ATM type %d\n",
			 vcc->qos.aal);
		return -EINVAL;
	}

	skb = alloc_skb(sizeof(*header), GFP_KERNEL);
	if (!skb) {
		if (net_ratelimit())
			dev_warn(&card->dev->dev, "Failed to allocate sk_buff in popen()\n");
		return -ENOMEM;
	}
	header = (void *)skb_put(skb, sizeof(*header));

	header->size = cpu_to_le16(0);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_POPEN);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, NULL);

	set_bit(ATM_VF_ADDR, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	return 0;
}
