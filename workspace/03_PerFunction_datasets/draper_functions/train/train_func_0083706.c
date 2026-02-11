updateLayout()
{
	char *bpango;

	if (!textdata)
		pango_layout_set_text(layout,"",-1);
	else
	{
		if (markup)
		{
			bpango = gt_html_to_pango_string(textdata, -1, false);
			if (!bpango)
				pango_layout_set_text(layout,"",-1);
			else
			{
				pango_layout_set_markup(layout,bpango,-1);
				g_free(bpango);
			}
		}
		else
			pango_layout_set_text(layout,textdata,-1);
	}

	gt_add_layout_from_font(layout, font());
}
