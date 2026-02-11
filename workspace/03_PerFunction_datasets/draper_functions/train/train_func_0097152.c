_draw_string(FT_Face face, const uint8_t *string, int length,
                        TEXTST_BITMAP *bmp, int x, int y,
                        BD_TEXTST_REGION_STYLE *style,
                        int *baseline_pos)
{
    uint8_t  color = style->font_color;
    unsigned char_code;
    int      ii, jj, kk;
    unsigned flags;

    if (length <= 0) {
        return -1;
    }
    if (!bmp) {
        flags = FT_LOAD_DEFAULT;
    } else {
        flags = FT_LOAD_RENDER;
    }

    for (ii = 0; ii < length; ii++) {

            int char_size = _utf8_char_size(string + ii);
            char_code = _utf8_char_get(string + ii, char_size);
            ii += char_size - 1;


        if (FT_Load_Char(face, char_code, flags ) == 0) {

            if (style->font_style.bold && !(face->style_flags & FT_STYLE_FLAG_BOLD)) {
                FT_GlyphSlot_Embolden( face->glyph );
            }
            if (style->font_style.italic && !(face->style_flags & FT_STYLE_FLAG_ITALIC)) {
                FT_GlyphSlot_Oblique( face->glyph );
            }

            if (bmp) {
                for (jj = 0; jj < face->glyph->bitmap.rows; jj++) {
                    for (kk = 0; kk < face->glyph->bitmap.width; kk++) {
                        uint8_t pixel = face->glyph->bitmap.buffer[jj * face->glyph->bitmap.pitch + kk];
                        if (pixel & 0x80) {
                            int xpos = x + face->glyph->bitmap_left + kk;
                            int ypos = y - face->glyph->bitmap_top + jj;
                            if (xpos >= 0 && xpos < bmp->width && ypos >= 0 && ypos < bmp->height) {
                                bmp->mem[xpos + ypos * bmp->stride] = color;
                            }
                        }
                    }
                }
            }


            if (baseline_pos) {
                *baseline_pos = BD_MAX(*baseline_pos, (face->size->metrics.ascender >> 6) + 1);
            }

            x += face->glyph->metrics.horiAdvance >> 6;
        }
    }

    return x;
}
