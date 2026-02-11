count_cluster_cells(char_u *s, PangoItem *item,
		    PangoGlyphString* glyphs, int i,
		    int *cluster_width,
		    int *last_glyph_rbearing)
{
    char_u  *p;
    int	    next;
    int	    start, end;
    int	    width;
    int	    uc;
    int	    cellcount = 0;

    width = glyphs->glyphs[i].geometry.width;

    for (next = i + 1; next < glyphs->num_glyphs; ++next)
    {
	if (glyphs->glyphs[next].attr.is_cluster_start)
	    break;
	else if (glyphs->glyphs[next].geometry.width > width)
	    width = glyphs->glyphs[next].geometry.width;
    }

    start = item->offset + glyphs->log_clusters[i];
    end   = item->offset + ((next < glyphs->num_glyphs) ?
			    glyphs->log_clusters[next] : item->length);

    for (p = s + start; p < s + end; p += utf_byte2len(*p))
    {
	uc = utf_ptr2char(p);
	if (uc < 0x80)
	    ++cellcount;
	else if (!utf_iscomposing(uc))
	    cellcount += utf_char2cells(uc);
    }

    if (last_glyph_rbearing != NULL
	    && cellcount > 0 && next == glyphs->num_glyphs)
    {
	PangoRectangle ink_rect;


	pango_font_get_glyph_extents(item->analysis.font,
				     glyphs->glyphs[i].glyph,
				     &ink_rect, NULL);

	if (PANGO_RBEARING(ink_rect) > 0)
	    *last_glyph_rbearing = PANGO_RBEARING(ink_rect);
    }

    if (cellcount > 0)
	*cluster_width = width;

    return cellcount;
}
