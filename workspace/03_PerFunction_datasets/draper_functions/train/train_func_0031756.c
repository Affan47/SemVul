msb_mark_block_unused(struct msb_data *msb, int pba)
{
	int zone = msb_get_zone_from_pba(pba);

	if (!test_bit(pba, msb->used_blocks_bitmap)) {
		pr_err("BUG: attempt to mark already unused pba %d as unused" , pba);
		msb->read_only = true;
		return;
	}

	if (msb_validate_used_block_bitmap(msb))
		return;


	__clear_bit(pba, msb->used_blocks_bitmap);
	msb->free_block_count[zone]++;
}
