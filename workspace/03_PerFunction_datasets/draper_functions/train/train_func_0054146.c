mf_setline(mf, ptr)
MFILE *mf ;
char *ptr ;
{
    int lineno ;

    lineno = mf_locate_in(mf, ptr) ;
    if (lineno < 0) {
	fatal("ptr not in mf", mf->mf_name) ;
    }
    mf->mf_curline = lineno - 1 ;


}
