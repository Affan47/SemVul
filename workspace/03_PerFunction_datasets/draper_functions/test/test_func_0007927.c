odf_text_p_apply_style (OOParseState *state,
			PangoAttrList *attrs,
			int start, int end)
{
	oo_text_p_t *ptr;
	odf_text_p_apply_style_t data;

	if (attrs == NULL)
		return;

	g_return_if_fail (state->text_p_stack != NULL);
	ptr = state->text_p_stack->data;

	if (ptr->attrs == NULL)
		ptr->attrs = pango_attr_list_new ();

	data.start = start;
	data.end = end;
	data.attrs = ptr->attrs;

	pango_attr_list_filter (attrs, odf_text_p_apply_pango_attribute, &data);
}
