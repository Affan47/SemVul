shadow_draw_string(FT_Face face, int x, int y, wchar_t *str, int align)
{
    struct glyph   *glyphs;
    FT_UInt        gi,pgi;
    FT_Vector      delta,pen;
    FT_Glyph       image;
    FT_BitmapGlyph bit;
    size_t         len;
    int            i,ng,pos;
    int            kerning,scalable;

    len = wcslen(str);
    glyphs = malloc(sizeof(*glyphs) * len);
    memset(glyphs,0,sizeof(*glyphs) * len);

    kerning  = FT_HAS_KERNING(face);
    scalable = FT_IS_SCALABLE(face);
    pgi = 0;

    for (ng = 0, pos = 0, i = 0; str[i] != 0; i++) {
	gi = FT_Get_Char_Index(face, str[i]);
	if (kerning && pgi && gi) {
	    FT_Get_Kerning(face,pgi,gi,FT_KERNING_DEFAULT,&delta);
	    pos += delta.x;
	}
	glyphs[ng].pos = pos;
	if (0 != FT_Load_Glyph(face, gi, FT_LOAD_DEFAULT))
	    continue;
	if (0 != FT_Get_Glyph(face->glyph, &glyphs[ng].glyph))
	    continue;
	pos += face->glyph->advance.x;
	pgi = gi;
	ng++;
    }

    switch(align) {
    case -1:
	break;
    case 0:
	x -= pos >> 7;
	break;
    case 1:
	x -= pos >> 6;
	break;
    }
    pen.x = 0;
    pen.y = 0;
    for (i = 0; i < ng; i++) {
	image = glyphs[i].glyph;
	if (0 != FT_Glyph_To_Bitmap(&image,FT_RENDER_MODE_NORMAL,&pen,0))
	    continue;
	bit = (FT_BitmapGlyph)image;
	shadow_draw_glyph(&bit->bitmap,
			  x + bit->left + (glyphs[i].pos >> 6),
			  y - bit->top);
	if (image != glyphs[i].glyph)
	    FT_Done_Glyph(image);
    }

    for (i = 0; i < ng; i++)
	FT_Done_Glyph(glyphs[i].glyph);
    free(glyphs);

    return pos >> 6;
}
