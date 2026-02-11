pixmap_save_targa(GwyContainer *data,
                  const gchar *filename,
                  GwyRunType mode,
                  GError **error)
{
   static guchar targa_head[] = {
     0,
     0,
     2,
     0, 0, 0, 0,
     0,
     0, 0, 0, 0,
     0, 0,
     0, 0,
     24,
     0x20,
    };
    GwyPixbuf *pixbuf;
    guchar *buffer = NULL;
    guint i, j;
    gboolean ok = FALSE;
    FILE *fh;

    pixbuf = pixmap_draw_pixbuf(data, "TARGA", FALSE, mode, error);
    if (!pixbuf)
        return FALSE;

    if (pixbuf->height >= 65535 || pixbuf->width >= 65535) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Image is too large to be stored as TARGA."));
        return FALSE;
    }

    *(guint16*)(targa_head + 12) = GUINT16_TO_LE((guint16)pixbuf->width);
    *(guint16*)(targa_head + 14) = GUINT16_TO_LE((guint16)pixbuf->height);

    fh = g_fopen(filename, "wb");
    if (!fh) {
        err_OPEN_WRITE(error);
        gwy_pixbuf_free(pixbuf);
        return FALSE;
    }

    if (fwrite(targa_head, 1, sizeof(targa_head), fh) != sizeof(targa_head)) {
        err_WRITE(error);
        goto end;
    }


    buffer = g_new(guchar, pixbuf->rowstride);
    memset(buffer, 0xff, pixbuf->rowstride);
    for (i = 0; i < pixbuf->height; i++) {
        const guchar *p = (const guchar*)pixbuf->pixels + i*pixbuf->rowstride;
        guchar *q = buffer;

        for (j = pixbuf->width; j; j--, p += 3, q += 3) {
            *q = *(p + 2);
            *(q + 1) = *(p + 1);
            *(q + 2) = *p;
        }
        if (!fwrite(buffer, pixbuf->rowstride, 1, fh)) {
            err_WRITE(error);
            goto end;
        }
    }

    ok = TRUE;
end:
    gwy_pixbuf_free(pixbuf);
    g_free(buffer);
    fclose(fh);

    return ok;
}
