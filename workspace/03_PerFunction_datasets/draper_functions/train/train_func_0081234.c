_dxfmatchint(struct finfo *f, int *ip)
{
    Error rc = OK;

#if DEBUG_MSG
    if (DXQueryDebug("T")) {
	DXDebug("T", "looking for an integer");
	DXDebug("T", "last token = %s", _dxfprtoken(&f->t, f->d));
    }
#endif

    if(f->t.class == NUMBER && f->t.subclass == INTEGER) {
	*ip = f->t.token.i;
        rc = _dxflexinput(f);
        return rc;
    }

    return ERROR;
}
