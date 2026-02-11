ksz_alloc_soft_desc(struct ksz_desc_info *desc_info, int transmit)
{
	desc_info->ring = kzalloc(sizeof(struct ksz_desc) * desc_info->alloc,
				  GFP_KERNEL);
	if (!desc_info->ring)
		return 1;
	hw_init_desc(desc_info, transmit);
	return 0;
}
