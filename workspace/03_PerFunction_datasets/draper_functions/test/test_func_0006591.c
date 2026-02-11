xfs_inobt_update(
	struct xfs_btree_cur	*cur,
	xfs_inobt_rec_incore_t	*irec)
{
	union xfs_btree_rec	rec;

	rec.inobt.ir_startino = cpu_to_be32(irec->ir_startino);
	if (xfs_sb_version_hassparseinodes(&cur->bc_mp->m_sb)) {
		rec.inobt.ir_u.sp.ir_holemask = cpu_to_be16(irec->ir_holemask);
		rec.inobt.ir_u.sp.ir_count = irec->ir_count;
		rec.inobt.ir_u.sp.ir_freecount = irec->ir_freecount;
	} else {

		rec.inobt.ir_u.f.ir_freecount = cpu_to_be32(irec->ir_freecount);
	}
	rec.inobt.ir_free = cpu_to_be64(irec->ir_free);
	return xfs_btree_update(cur, &rec);
}
