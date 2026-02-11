emboss24(void *data, struct taskinfo *task, int r1, int r2)
{
    pixel8_t *src, *srcend, *src2;
    pixel8_t *dest;
    struct filter *f = (struct filter *) data;
    struct embossdata *s = (struct embossdata *) f->data;
    int i;
    unsigned int *table = s->table;
    for (i = r1; i < r2; i++) {
	src = f->childimage->currlines[i];
	src2 = f->childimage->currlines[i + s->ydist] + s->xdist;
	srcend = src + f->image->width;
	dest = (pixel8_t *) f->image->currlines[i];
	while (src < srcend) {
	    *dest = *(dest + 1) = *(dest + 2) =
		table[((int) *src2 - (int) *src) & 511];
	    src++;
	    src2++;
	    dest += 3;
	}
    }
}
