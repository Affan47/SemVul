_dxfnexttoken(struct finfo *f, int *class, int *subclass, int *id)
{
#if DEBUG_MSG
    if (DXQueryDebug("T"))
	DXDebug("T", "last token = %s", _dxfprtoken(&f->t, f->d));
#endif

    if (class)
	*class = f->t.class;

    if (subclass)
	*subclass = f->t.subclass;

    if (id)
	*id = f->t.token.id;

    return f->t.class == LEXERROR ? ERROR : OK;
}
