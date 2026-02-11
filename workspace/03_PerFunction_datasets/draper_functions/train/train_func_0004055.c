gfxr_endianness_adjust(gfx_pixmap_t *pixmap, gfx_mode_t *mode)
{
        int bytespp;
        byte *data;

        if (!pixmap || !pixmap->data || !mode) {
                GFXERROR("gfxr_endianness_adjust(): Invoked with invalid values\n");
		BREAKPOINT();
                return NULL;
        }

        if (!(mode->flags & GFX_MODE_FLAG_REVERSE_ENDIAN))
                return pixmap;

        bytespp = mode->bytespp;

        data = pixmap->data;

        switch (bytespp) {
        case 1:
                break;

        case 2: pixmap_endianness_reverse_2(data, pixmap->xl
                                            * pixmap->yl);
        break;

        case 3: pixmap_endianness_reverse_3_simple(data, pixmap->xl
                                            * pixmap->yl);
        break;

        case 4: pixmap_endianness_reverse_4(data, pixmap->xl * pixmap->yl);
        break;

        default: fprintf(stderr,"gfxr_endianness_adjust(): Cannot adjust endianness for %d bytespp!\n", bytespp);
                return NULL;
        }

        return pixmap;
}
