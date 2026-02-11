mark_trailer(pdf_document *xref, pdf_write_options *opts, pdf_obj *dict)
{
	fz_context *ctx = xref->ctx;
	int i, n = pdf_dict_len(dict);

	if (pdf_dict_mark(dict))
		return;

	fz_try(ctx)
	{
		for (i = 0; i < n; i++)
		{
			char *key = pdf_to_name(pdf_dict_get_key(dict, i));
			pdf_obj *val = pdf_dict_get_val(dict, i);

			if (!strcmp("Root", key))
				mark_root(xref, opts, val);
			else
				mark_all(xref, opts, val, USE_CATALOGUE, -1);
		}
	}
	fz_always(ctx)
	{
		pdf_dict_unmark(dict);
	}
	fz_catch(ctx)
	{
		fz_rethrow(ctx);
	}
}
