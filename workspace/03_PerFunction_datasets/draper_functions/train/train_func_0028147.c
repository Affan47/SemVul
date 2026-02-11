mf_put(mfp, hp, dirty, infile)
    memfile_T	*mfp;
    bhdr_T	*hp;
    int		dirty;
    int		infile;
{
    int		flags;

    flags = hp->bh_flags;

    if ((flags & BH_LOCKED) == 0)
	EMSG(_("E293: block was not locked"));
    flags &= ~BH_LOCKED;
    if (dirty)
    {
	flags |= BH_DIRTY;
	mfp->mf_dirty = TRUE;
    }
    hp->bh_flags = flags;
    if (infile)
	mf_trans_add(mfp, hp);
}
