define_pattern(int i, int c, Svg_data *data)
{
    int j, k, l;
    fRGB *frgb;
    double bg_red, bg_green, bg_blue;

    if (data->pattern_defined[i] == TRUE && c < number_of_colors() && data->colorfilter_defined[c] == TRUE) {
        return;
    }

    if (data->pattern_defined[i] != TRUE) {

        data->pattern_empty[i] = TRUE;
        data->pattern_full[i]  = TRUE;
        for (j = 0; j < 32; j++) {
            if (pat_bits[i][j] != 0x00) {
                data->pattern_empty[i] = FALSE;
            }
            if (pat_bits[i][j] != 0xff) {
                data->pattern_full[i] = FALSE;
            }
        }
    }

    if (data->pattern_empty[i] != TRUE && data->pattern_full[i] != TRUE) {
        fprintf(prstream, "  <defs>\n");

        if (data->pattern_defined[i] != TRUE) {


            fprintf(prstream,
                    "   <pattern id=\"pattern%d\" viewBox=\"0 0 16 16\""
                    " width=\"%d\" height=\"%d\" patternUnits=\"userSpaceOnUse\">\n",
                    i, 16, 16);
            fprintf(prstream,"     <rect fill=\"#FFFFFF\" x=\"0\" y=\"0\""
                            " width=\"16\" height=\"16\"/>\n");
            for (j = 0; j < 256; j++) {
                k = j/16;
                l = j%16;
                if ((pat_bits[i][j/8] >> (j%8)) & 0x01) {

                    fprintf(prstream,
                            "     <rect x=\"%d\" y=\"%d\""
                            " width=\"1\" height=\"1\"/>\n",
                            l, 15-k);
                }
            }
            fprintf(prstream, "   </pattern>\n");
            data->pattern_defined[i] = TRUE;
        }


        if (c < number_of_colors() && data->colorfilter_defined[c] != TRUE) {
            frgb = get_frgb(getbgcolor());
            bg_red=frgb->red;
            bg_green=frgb->green;
            bg_blue=frgb->blue;
            frgb = get_frgb(c);
            fprintf(prstream, "   <filter id=\"tocolor%d\" filterUnits=\"objectBoundingBox\"\n", c);
            fprintf(prstream, "    color-interpolation-filters=\"sRGB\" x=\"0%%\" y=\"0%%\" width=\"100%%\" height=\"100%%\">\n");
            fprintf(prstream, "    <feComponentTransfer>\n");
            fprintf(prstream, "      <feFuncR type=\"discrete\" tableValues=\"%.6f %.6f\"/>\n",
                    frgb->red, bg_red);
            fprintf(prstream, "      <feFuncG type=\"discrete\" tableValues=\"%.6f %.6f\"/>\n",
                    frgb->green, bg_green);
            fprintf(prstream, "      <feFuncB type=\"discrete\" tableValues=\"%.6f %.6f\"/>\n",
                    frgb->blue, bg_blue);
            fprintf(prstream, "    </feComponentTransfer>\n");
            fprintf(prstream, "   </filter>\n");
            data->colorfilter_defined[c] = TRUE;
        }
        fprintf(prstream, "  </defs>\n");
    }
}
