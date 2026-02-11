fz_bound_ft_glyph(fz_context *ctx, fz_font *font, int gid, fz_matrix trm)
{
	FT_Face face = font->ft_face;
	FT_Error fterr;
	FT_BBox cbox;
	FT_Matrix m;
	FT_Vector v;
	fz_rect bounds;


	float strength = fz_matrix_expansion(trm) * 0.02f;

	trm = fz_adjust_ft_glyph_width(ctx, font, gid, trm);

	if (font->ft_italic)
		trm = fz_concat(fz_shear(SHEAR, 0), trm);

	m.xx = trm.a * 64;
	m.yx = trm.b * 64;
	m.xy = trm.c * 64;
	m.yy = trm.d * 64;
	v.x = trm.e * 64;
	v.y = trm.f * 64;

	fz_lock(ctx, FZ_LOCK_FREETYPE);
	fterr = FT_Set_Char_Size(face, 65536, 65536, 72, 72);
	if (fterr)
		fz_warn(ctx, "freetype setting character size: %s", ft_error_string(fterr));
	FT_Set_Transform(face, &m, &v);

	fterr = FT_Load_Glyph(face, gid, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING);
	if (fterr)
	{
		fz_warn(ctx, "freetype load glyph (gid %d): %s", gid, ft_error_string(fterr));
		fz_unlock(ctx, FZ_LOCK_FREETYPE);
		bounds.x0 = bounds.x1 = trm.e;
		bounds.y0 = bounds.y1 = trm.f;
		return bounds;
	}

	if (font->ft_bold)
	{
		FT_Outline_Embolden(&face->glyph->outline, strength * 64);
		FT_Outline_Translate(&face->glyph->outline, -strength * 32, -strength * 32);
	}

	FT_Outline_Get_CBox(&face->glyph->outline, &cbox);
	fz_unlock(ctx, FZ_LOCK_FREETYPE);
	bounds.x0 = cbox.xMin / 64.0f;
	bounds.y0 = cbox.yMin / 64.0f;
	bounds.x1 = cbox.xMax / 64.0f;
	bounds.y1 = cbox.yMax / 64.0f;

	if (fz_is_empty_rect(bounds))
	{
		bounds.x0 = bounds.x1 = trm.e;
		bounds.y0 = bounds.y1 = trm.f;
	}

	return bounds;
}
