get_text_widget_info(pdf_document *doc, pdf_obj *widget, text_widget_info *info)
{
	char *da = pdf_to_str_buf(get_inheritable(doc, widget, "DA"));
	int ff = get_field_flags(doc, widget);
	pdf_obj *ml = get_inheritable(doc, widget, "MaxLen");

	info->dr = get_inheritable(doc, widget, "DR");
	info->q = pdf_to_int(get_inheritable(doc, widget, "Q"));
	info->multiline = (ff & Ff_Multiline) != 0;
	info->comb = (ff & (Ff_Multiline|Ff_Password|Ff_FileSelect|Ff_Comb)) == Ff_Comb;

	if (ml == NULL)
		info->comb = 0;
	else
		info->max_len = pdf_to_int(ml);

	get_font_info(doc, info->dr, da, &info->font_rec);
}
