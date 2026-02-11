gGraphCreateFont (double size, int style, int weight, const void **font)
{

    gGraphFontPtr fnt;

    *font = NULL;
    fnt = malloc (sizeof (gGraphFont));
    if (!fnt)
	return GGRAPH_INSUFFICIENT_MEMORY;
    fnt->signature = GG_GRAPHICS_FONT_MAGIC_SIGNATURE;
    if (size < 1.0)
	fnt->size = 1.0;
    else if (size > 32.0)
	fnt->size = 32.0;
    else
	fnt->size = size;
    if (style == GGRAPH_FONTSTYLE_ITALIC)
	fnt->style = GGRAPH_FONTSTYLE_ITALIC;
    else
	fnt->style = GGRAPH_FONTSTYLE_NORMAL;
    if (weight == GGRAPH_FONTWEIGHT_BOLD)
	fnt->weight = GGRAPH_FONTWEIGHT_BOLD;
    else
	fnt->weight = GGRAPH_FONTWEIGHT_NORMAL;
    fnt->is_outlined = 0;
    fnt->outline_width = 0.0;
    fnt->red = 0.0;
    fnt->green = 0.0;
    fnt->blue = 0.0;
    fnt->alpha = 1.0;
    *font = fnt;
    return GGRAPH_OK;
}
