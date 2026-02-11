send_command(struct solos_card *card, int dev, const char *buf, size_t size)
{
	struct sk_buff *skb;
	struct pkt_hdr *header;

	if (size > (BUF_SIZE - sizeof(*header))) {
		dev_dbg(&card->dev->dev, "Command is too big.  Dropping request\n");
		return 0;
	}
	skb = alloc_skb(size + sizeof(*header), GFP_ATOMIC);
	if (!skb) {
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in send_command()\n");
		return 0;
	}

	header = (void *)skb_put(skb, sizeof(*header));

	header->size = cpu_to_le16(size);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	memcpy(skb_put(skb, size), buf, size);

	fpga_queue(card, dev, skb, NULL);

	return 0;
}
