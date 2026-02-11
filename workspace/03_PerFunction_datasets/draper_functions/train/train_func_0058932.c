pdf_choice_widget_is_multiselect(pdf_document *doc, fz_widget *tw)
{
	pdf_annot *annot = (pdf_annot *)tw;

	if (!annot) return 0;

	switch(pdf_field_type(doc, annot->obj))
	{
	case FZ_WIDGET_TYPE_LISTBOX:
	case FZ_WIDGET_TYPE_COMBOBOX:
		return (get_field_flags(doc, annot->obj) & Ff_MultiSelect) != 0;
	default:
		return 0;
	}
}
