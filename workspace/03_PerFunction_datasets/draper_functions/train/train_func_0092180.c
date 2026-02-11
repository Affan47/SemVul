layouts_overlapping(struct nfs4_layout *lo, struct nfsd4_layout_seg *s)
{
	if (s->iomode != IOMODE_ANY && s->iomode != lo->lo_seg.iomode)
		return false;
	if (layout_end(&lo->lo_seg) <= s->offset)
		return false;
	if (layout_end(s) <= lo->lo_seg.offset)
		return false;
	return true;
}
