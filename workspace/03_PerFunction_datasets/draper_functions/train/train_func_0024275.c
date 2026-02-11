mf_kilbuf(mf)
MFILE *mf;
{
    MFILE *tmp ;

    if (mf == mf_structlist) {
	mf_structlist = mf->mf_next ;
    } else {
	for (tmp = mf_structlist; tmp->mf_next != NULL; tmp = tmp->mf_next) {
	    if (tmp->mf_next == mf) {
		tmp->mf_next = mf->mf_next ;
	    }
	}
	if (tmp->mf_next == NULL) {
#ifdef DEBUG
	    fatal("freeing spurious buffer", mf->mf_name) ;
#endif
	    return ;
	}
    }
    free(mf->mf_name) ;
    free(mf->mf_buffer) ;
    free(mf->mf_lbeg) ;
    free(mf) ;
}
