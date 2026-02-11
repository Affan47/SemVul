bam_plp_set_mask(bam_plp_t iter, int mask)
{
	iter->flag_mask = mask < 0? BAM_DEF_MASK : (BAM_FUNMAP | mask);
}
