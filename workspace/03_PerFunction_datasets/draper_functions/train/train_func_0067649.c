go_style_persist_sax_save (GOPersist const *gp, GsfXMLOut *output)
{
	GOStyle const *style = GO_STYLE (gp);

	gsf_xml_out_add_cstr_unchecked (output, "type",
		G_OBJECT_TYPE_NAME (style));

	if (style->interesting_fields & GO_STYLE_OUTLINE)
		go_style_line_sax_save (output, "outline", &style->line);
	if (style->interesting_fields & GO_STYLE_LINE)
		go_style_line_sax_save (output, "line", &style->line);
	if (style->interesting_fields & GO_STYLE_FILL)
		go_style_fill_sax_save (output, style);
	if (style->interesting_fields & GO_STYLE_MARKER)
		go_style_marker_sax_save (output, style);
	if (style->interesting_fields & GO_STYLE_FONT)
		go_style_font_sax_save (output, style);
	if (style->interesting_fields & GO_STYLE_TEXT_LAYOUT)
		go_style_text_layout_sax_save (output, style);
}
