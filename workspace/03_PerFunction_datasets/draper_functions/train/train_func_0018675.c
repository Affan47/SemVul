shadow_draw_string_cursor(FT_Face face, int x, int y, wchar_t *str, int pos)
{
    wchar_t save;
    int len, left, width, y1, y2;

    len = wcslen(str);
    if (pos >= len) {
	left  = shadow_draw_string(face, x, y, str, -1);
	width = shadow_draw_string(face, x+left, y, L" ", -1);
    } else {
	save = str[pos];
	str[pos] = 0;
	left = shadow_draw_string(face, x, y, str, -1);
	str[pos] = save;

	save = str[pos+1];
	str[pos+1] = 0;
	width = shadow_draw_string(face, x+left, y, str+pos, -1);
	str[pos+1] = save;

	shadow_draw_string(face, x+left+width, y, str+pos+1, -1);
    }

    y2 = y  - (face->size->metrics.descender >> 6) -1;
    y1 = y2 - (face->size->metrics.height    >> 6) +1;
    shadow_reverse(left,left+width,y1,y2);
}
