uih_redo(struct uih_context *c)
{
    xio_file f;
    int pos = c->undo.last;
    if (c->undo.undos[pos]) {
	f = xio_strropen(c->undo.undos[pos]);
	c->undo.undos[pos] = NULL;
	c->undo.last = pos;
	uih_load(c, f, "");
    }
}
