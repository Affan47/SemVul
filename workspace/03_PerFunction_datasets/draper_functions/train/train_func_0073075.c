get_id(u8 *id_array,
					int max_ids,
					int base_id,
					const char *thread_name)
{
	struct pti_masterchannel *mc;
	int i, j, mask;

	mc = kmalloc(sizeof(struct pti_masterchannel), GFP_KERNEL);
	if (mc == NULL)
		return NULL;


	for (i = 0; i < max_ids; i++)
		if (id_array[i] != 0xff)
			break;
	if (i == max_ids) {
		kfree(mc);
		return NULL;
	}

	mask = 0x80;
	for (j = 0; j < 8; j++) {
		if ((id_array[i] & mask) == 0)
			break;
		mask >>= 1;
	}


	id_array[i] |= mask;
	mc->master  = base_id;
	mc->channel = ((i & 0xf)<<3) + j;

	pti_control_frame_built_and_sent(mc, thread_name);
	return mc;
}
