destroyinstance(struct filter *f)
{
    if (f->data != NULL)
	destroypalette((struct palette *) f->data);
    destroyinheredimage(f);
    free(f);
}
