_bdf_widen_by(bdf_font_t *f, bdf_glyph_t *g, bdf_bitmap_t *s, int n)
#else
_bdf_widen_by(f, g, s, n)
bdf_font_t *f;
bdf_glyph_t *g;
bdf_bitmap_t *s;
int n;
#endif
{
    int bytes, sbpr, dbpr, col;
    short x, y, si, di;
    unsigned char *bmap, *masks;

    masks = 0;
    switch (f->bpp) {
      case 1: masks = onebpp; break;
      case 2: masks = twobpp; break;
      case 4: masks = fourbpp; break;
    }

    s->height = g->bbx.height;
    s->width = g->bbx.width + n;

    bytes = (((s->width * f->bpp) + 7) >> 3) * s->height;

    if (s->bytes == 0)
      s->bitmap = (unsigned char *) malloc(bytes);
    else
      s->bitmap = (unsigned char *)
          realloc((char *) s->bitmap, bytes);
    s->bytes = bytes;

    (void) memset((char *) s->bitmap, 0, s->bytes);


    sbpr = ((g->bbx.width * f->bpp) + 7) >> 3;
    dbpr = ((s->width * f->bpp) + 7) >> 3;
    for (y = 0; y < g->bbx.height; y++) {
        for (col = x = 0; x < g->bbx.width; x++, col += f->bpp) {
            si = (col & 7) / f->bpp;
            bytes = g->bitmap[(y * sbpr) + (col >> 3)] & masks[si];
            if (bytes) {
                di = ((x * f->bpp) & 7) / f->bpp;
                if (di < si)
                  bytes <<= (si - di) * f->bpp;
                else if (di > si)
                  bytes >>= (di - si) * f->bpp;
                s->bitmap[(y * dbpr) + (col >> 3)] |= bytes;
            }
        }
    }
    g->bbx.width = s->width;


    bytes = g->bytes;
    g->bytes = s->bytes;
    s->bytes = bytes;

    bmap = g->bitmap;
    g->bitmap = s->bitmap;
    s->bitmap = bmap;
}
