wr_object_memory(void)
{
	int k_idx;

	wr_u16b(z_info->k_max);
	for (k_idx = 0; k_idx < z_info->k_max; k_idx++)
	{
		byte tmp8u = 0;
		object_kind *k_ptr = &k_info[k_idx];

		if (k_ptr->aware) tmp8u |= 0x01;
		if (k_ptr->tried) tmp8u |= 0x02;
		if (kind_is_squelched_aware(k_ptr)) tmp8u |= 0x04;
		if (k_ptr->everseen) tmp8u |= 0x08;
		if (kind_is_squelched_unaware(k_ptr)) tmp8u |= 0x10;

		wr_byte(tmp8u);
	}
}
