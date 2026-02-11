pdf_text_widget_set_text(pdf_document *doc, fz_widget *tw, char *text)
{
	pdf_annot *annot = (pdf_annot *)tw;
	fz_context *ctx = doc->ctx;
	int accepted = 0;

	fz_try(ctx)
	{
		accepted = run_keystroke(doc, annot->obj, &text);
		if (accepted)
			accepted = pdf_field_set_value(doc, annot->obj, text);
	}
	fz_catch(ctx)
	{
		fz_warn(ctx, "fz_text_widget_set_text failed");
	}

	return accepted;
}
