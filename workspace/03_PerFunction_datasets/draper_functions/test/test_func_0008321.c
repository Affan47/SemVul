setup_panel_style(GkrellmPanel *p, GkrellmStyle *style)
	{
	GkrellmLabel	*lbl	= p->label;

	p->style = style;
	if (!style)
		return;
	lbl->position = style->label_position;
	p->transparency = style->transparency;
	p->scroll_text_cache_off = style->scroll_text_cache_off;
	_GK.any_transparency |= p->transparency;
	if (!p->textstyle)
		{
		p->textstyle = gkrellm_textstyle_new0();
		p->textstyle->internal = TRUE;
		}
	if (p->textstyle->internal)
		{
		*(p->textstyle) = style->label_tsA;
		p->textstyle->internal = TRUE;
		p->textstyle->font = *(style->label_tsA.font_seed);
		}
	}
