bdf_export_hex(FILE *out, bdf_font_t *font, bdf_callback_t callback,
               void *data)
#else
bdf_export_hex(out, font, callback, data)
FILE *out;
bdf_font_t *font;
bdf_callback_t callback;
void *data;
#endif
{
    int bpr, fbpr, j, k;
    unsigned long i, ng;
    bdf_glyph_t *gp, cell;
    bdf_callback_struct_t cb;

    if (font == 0 || out == 0)
      return;

    if (font->glyphs_used == 0)
      return;


    if (callback != 0) {
        cb.reason = BDF_EXPORT_START;
        cb.total = font->glyphs_used;
        cb.current = 0;
        (*callback)(&cb, data);
    }

    fbpr = ((font->bbx.width * font->bpp) + 7) >> 3;
    bpr = (((font->bbx.width >> 1) * font->bpp) + 7) >> 3;
    cell.bytes = fbpr * font->bbx.height;
    cell.bitmap = (unsigned char *) malloc(cell.bytes);

    for (i = 0, ng = font->glyphs_used, gp = font->glyphs; i < ng; i++, gp++) {
        _bdf_pad_cell(font, gp, &cell);
        fprintf(out, "%04lX:", gp->encoding & 0xffff);
        if (gp->bbx.width <= (font->bbx.width >> 1)) {
            for (j = 0; j < cell.bytes; j += fbpr) {
                for (k = 0; k < bpr; k++)
                  fprintf(out, "%02X", cell.bitmap[j + k]);
            }
        } else {
            for (j = 0; j < cell.bytes; j++)
              fprintf(out, "%02X", cell.bitmap[j]);
        }
        if (cell.bytes > 0)
          putc('\n', out);


        if (callback != 0) {
            cb.reason = BDF_EXPORTING;
            cb.current++;
            (*callback)(&cb, data);
        }
    }


    free((char *) cell.bitmap);


    if (callback != 0) {
        cb.reason = BDF_EXPORTING;
        cb.current = cb.total;
        (*callback)(&cb, data);
    }
}
