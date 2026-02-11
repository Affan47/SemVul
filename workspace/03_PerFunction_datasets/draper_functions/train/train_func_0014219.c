mf_ins_used(mfp, hp)
    memfile_T	*mfp;
    bhdr_T	*hp;
{
    hp->bh_next = mfp->mf_used_first;
    mfp->mf_used_first = hp;
    hp->bh_prev = NULL;
    if (hp->bh_next == NULL)
	mfp->mf_used_last = hp;
    else
	hp->bh_next->bh_prev = hp;
    mfp->mf_used_count += hp->bh_page_count;
    total_mem_used += hp->bh_page_count * mfp->mf_page_size;
}
