FcFreeTypeCheckGlyph (FT_Face face, FcChar32 ucs4,
		      FT_UInt glyph, FcBlanks *blanks,
		      FT_Pos *advance,
		      FcBool using_strike)
{
    FT_Int	    load_flags = FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH | FT_LOAD_NO_SCALE | FT_LOAD_NO_HINTING;
    FT_GlyphSlot    slot;

    if (using_strike)
	load_flags &= ~FT_LOAD_NO_SCALE;


    if (face->face_flags & FT_FACE_FLAG_SCALABLE)
	load_flags |= FT_LOAD_NO_BITMAP;

    if (FT_Load_Glyph (face, glyph, load_flags))
	return FcFalse;

    slot = face->glyph;
    if (!glyph)
	return FcFalse;

    *advance = slot->metrics.horiAdvance;

    switch (slot->format) {
    case ft_glyph_format_bitmap:


	return FcTrue;
    case ft_glyph_format_outline:


	if (slot->outline.n_contours != 0)
	    return FcTrue;


	if (!blanks || FcBlanksIsMember (blanks, ucs4))
	    return FcTrue;

    default:
	break;
    }
    return FcFalse;
}
