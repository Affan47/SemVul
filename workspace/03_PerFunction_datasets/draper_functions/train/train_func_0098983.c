au_di_cp(struct au_dinfo *dst, struct au_dinfo *src)
{
	AuRwMustWriteLock(&dst->di_rwsem);
	AuRwMustWriteLock(&src->di_rwsem);

	dst->di_bstart = src->di_bstart;
	dst->di_bend = src->di_bend;
	dst->di_bwh = src->di_bwh;
	dst->di_bdiropq = src->di_bdiropq;

}
