vac_cmp_vtlinks(const void *left, const void *right)
{
	if (((VTupleLink) left)->new_tid.ip_blkid.bi_hi <
		((VTupleLink) right)->new_tid.ip_blkid.bi_hi)
		return -1;
	if (((VTupleLink) left)->new_tid.ip_blkid.bi_hi >
		((VTupleLink) right)->new_tid.ip_blkid.bi_hi)
		return 1;

	if (((VTupleLink) left)->new_tid.ip_blkid.bi_lo <
		((VTupleLink) right)->new_tid.ip_blkid.bi_lo)
		return -1;
	if (((VTupleLink) left)->new_tid.ip_blkid.bi_lo >
		((VTupleLink) right)->new_tid.ip_blkid.bi_lo)
		return 1;

	if (((VTupleLink) left)->new_tid.ip_posid <
		((VTupleLink) right)->new_tid.ip_posid)
		return -1;
	if (((VTupleLink) left)->new_tid.ip_posid >
		((VTupleLink) right)->new_tid.ip_posid)
		return 1;
	return 0;
}
