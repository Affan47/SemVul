get_chunk(struct super_block *sb, struct buffer_head *bh)
{
	char *bh_data = bh->b_data;

	if (SYSV_SB(sb)->s_type == FSTYPE_SYSV4)
		return (sysv_zone_t*)(bh_data+4);
	else
		return (sysv_zone_t*)(bh_data+2);
}
