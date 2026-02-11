pdf_field_set_value(pdf_document *doc, pdf_obj *field, char *text)
{
	pdf_obj *v = pdf_dict_getp(field, "AA/V");

	if (v && doc->js)
	{
		pdf_js_event e;

		e.target = field;
		e.value = text;
		pdf_js_setup_event(doc->js, &e);
		execute_action(doc, field, v);

		if (!pdf_js_get_event(doc->js)->rc)
			return 0;

		text = pdf_js_get_event(doc->js)->value;
	}

	doc->dirty = 1;
	update_text_field_value(doc->ctx, field, text);
	recalculate(doc);

	return 1;
}
