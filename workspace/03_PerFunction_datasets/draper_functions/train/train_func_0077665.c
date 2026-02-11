adi_id_decode(struct adi *adi, struct adi_port *port)
{
	int i, t;

	if (adi->ret < ADI_MIN_ID_LENGTH)
		return;

	if (adi->ret < (t = adi_get_bits(adi, 10))) {
		printk(KERN_WARNING "adi: Short ID packet: reported: %d != read: %d\n", t, adi->ret);
		return;
	}

	adi->id = adi_get_bits(adi, 4) | (adi_get_bits(adi, 4) << 4);

	if ((t = adi_get_bits(adi, 4)) & ADI_FLAG_HAT) adi->hats++;

	adi->length = adi_get_bits(adi, 10);

	if (adi->length >= ADI_MAX_LENGTH || adi->length < ADI_MIN_LENGTH) {
		printk(KERN_WARNING "adi: Bad data packet length (%d).\n", adi->length);
		adi->length = 0;
		return;
	}

	adi->axes8 = adi_get_bits(adi, 4);
	adi->buttons = adi_get_bits(adi, 6);

	if (adi_get_bits(adi, 6) != 8 && adi->hats) {
		printk(KERN_WARNING "adi: Other than 8-dir POVs not supported yet.\n");
		adi->length = 0;
		return;
	}

	adi->buttons += adi_get_bits(adi, 6);
	adi->hats += adi_get_bits(adi, 4);

	i = adi_get_bits(adi, 4);

	if (t & ADI_FLAG_10BIT) {
		adi->axes10 = adi->axes8 - i;
		adi->axes8 = i;
	}

	t = adi_get_bits(adi, 4);

	for (i = 0; i < t; i++)
		adi->cname[i] = adi_get_bits(adi, 8);
	adi->cname[i] = 0;

	t = 8 + adi->buttons + adi->axes10 * 10 + adi->axes8 * 8 + adi->hats * 4;
	if (adi->length != t && adi->length != t + (t & 1)) {
		printk(KERN_WARNING "adi: Expected length %d != data length %d\n", t, adi->length);
		adi->length = 0;
		return;
	}

	switch (adi->id) {
		case ADI_ID_TPD:
			adi->pad = 4;
			adi->buttons -= 4;
			break;
		case ADI_ID_WGP:
			adi->pad = 0;
			adi->buttons -= 4;
			break;
		default:
			adi->pad = -1;
			break;
	}
}
