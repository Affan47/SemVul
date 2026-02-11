getGlyph(boost::uint16_t code, float& advance)
{
    std::auto_ptr<SWF::ShapeRecord> glyph;

    FT_Error error = FT_Load_Char(_face, code, FT_LOAD_NO_BITMAP |
                                                FT_LOAD_NO_SCALE);

    if (error) {
        log_error(_("Error loading freetype outline glyph for char '%c' "
                    "(error: %d)"), code, error);
        return glyph;
    }


    advance = _face->glyph->metrics.horiAdvance * scale;
#ifdef GNASH_DEBUG_DEVICEFONTS
    log_debug("Advance value for glyph '%c' is %g (horiAdvance:%ld, "
                "scale:%g)", code, advance,
              _face->glyph->metrics.horiAdvance, scale);
#endif

    if ( _face->glyph->format != FT_GLYPH_FORMAT_OUTLINE )
    {
        unsigned long gf = _face->glyph->format;
        log_unimpl(_("FT_Load_Char() returned a glyph format != "
                     "FT_GLYPH_FORMAT_OUTLINE (%c%c%c%c)"),
            static_cast<char>((gf>>24)&0xff),
            static_cast<char>((gf>>16)&0xff),
            static_cast<char>((gf>>8)&0xff),
            static_cast<char>(gf&0xff));
        return glyph;
    }

    FT_Outline* outline = &(_face->glyph->outline);

    FT_Outline_Funcs walk;
    walk.move_to = OutlineWalker::walkMoveTo;
    walk.line_to = OutlineWalker::walkLineTo;
    walk.conic_to = OutlineWalker::walkConicTo;
    walk.cubic_to = OutlineWalker::walkCubicTo;
    walk.shift = 0;
    walk.delta = 0;

#ifdef DEBUG_OUTLINE_DECOMPOSITION
    log_debug("Decomposing glyph outline for DisplayObject %u", code);
#endif

    glyph.reset(new SWF::ShapeRecord);

    OutlineWalker walker(*glyph, scale);

    FT_Outline_Decompose(outline, &walk, &walker);
#ifdef DEBUG_OUTLINE_DECOMPOSITION
#if 0

    SWFRect bound; sh->compute_bound(&bound, VM::get().getSWFVersion());
    log_debug("Decomposed glyph for DisplayObject '%c' has bounds %s",
            code, bound.toString());
#endif
#endif

    walker.finish();

    return glyph;
}
