velocity_init_info(struct velocity_info *vptr,
				const struct velocity_info_tbl *info)
{
	vptr->chip_id = info->chip_id;
	vptr->tx.numq = info->txqueue;
	vptr->multicast_limit = MCAM_SIZE;
	spin_lock_init(&vptr->lock);
}
