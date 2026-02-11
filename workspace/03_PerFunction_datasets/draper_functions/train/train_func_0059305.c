FillRule(GB_PAINT *d, int set, int *value)
{
	if (set)
	{
		cairo_fill_rule_t v;

		switch(*value)
		{
			case GB_PAINT_FILL_RULE_EVEN_ODD: v = CAIRO_FILL_RULE_EVEN_ODD; break;
			case GB_PAINT_FILL_RULE_WINDING: default: v = CAIRO_FILL_RULE_WINDING;
		}

		cairo_set_fill_rule(CONTEXT(d), v);
	}
	else
	{
		switch(cairo_get_fill_rule(CONTEXT(d)))
		{
			case CAIRO_FILL_RULE_EVEN_ODD: *value = GB_PAINT_FILL_RULE_EVEN_ODD; break;
			case CAIRO_FILL_RULE_WINDING: default: *value = GB_PAINT_FILL_RULE_WINDING;
		}
	}
}
