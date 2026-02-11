hfcpci_empty_fifo(struct BCState *bcs, bzfifo_type *bz, u_char *bdata, int count)
{
	u_char *ptr, *ptr1, new_f2;
	struct sk_buff *skb;
	struct IsdnCardState *cs = bcs->cs;
	int total, maxlen, new_z2;
	z_type *zp;

	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "hfcpci_empty_fifo");
	zp = &bz->za[bz->f2];
	new_z2 = zp->z2 + count;
	if (new_z2 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z2 -= B_FIFO_SIZE;
	new_f2 = (bz->f2 + 1) & MAX_B_FRAMES;
	if ((count > HSCX_BUFMAX + 3) || (count < 4) ||
	    (*(bdata + (zp->z1 - B_SUB_VAL)))) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "hfcpci_empty_fifo: incoming packet invalid length %d or crc", count);
#ifdef ERROR_STATISTIC
		bcs->err_inv++;
#endif
		bz->za[new_f2].z2 = new_z2;
		bz->f2 = new_f2;
		skb = NULL;
	} else if (!(skb = dev_alloc_skb(count - 3)))
		printk(KERN_WARNING "HFCPCI: receive out of memory\n");
	else {
		total = count;
		count -= 3;
		ptr = skb_put(skb, count);

		if (zp->z2 + count <= B_FIFO_SIZE + B_SUB_VAL)
			maxlen = count;
		else
			maxlen = B_FIFO_SIZE + B_SUB_VAL - zp->z2;

		ptr1 = bdata + (zp->z2 - B_SUB_VAL);
		memcpy(ptr, ptr1, maxlen);
		count -= maxlen;

		if (count) {
			ptr += maxlen;
			ptr1 = bdata;
			memcpy(ptr, ptr1, count);
		}
		bz->za[new_f2].z2 = new_z2;
		bz->f2 = new_f2;

	}
	return (skb);
}
