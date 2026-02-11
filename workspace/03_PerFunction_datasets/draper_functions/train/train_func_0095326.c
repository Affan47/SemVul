fmarks_check_one(fm, name, buf)
    xfmark_T	*fm;
    char_u	*name;
    buf_T	*buf;
{
    if (fm->fmark.fnum == 0
	    && fm->fname != NULL
	    && fnamecmp(name, fm->fname) == 0)
    {
	fm->fmark.fnum = buf->b_fnum;
	vim_free(fm->fname);
	fm->fname = NULL;
    }
}
