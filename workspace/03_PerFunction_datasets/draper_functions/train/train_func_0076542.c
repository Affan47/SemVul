load_separation(pdf_document *xref, pdf_obj *array)
{
	fz_colorspace *cs;
	struct separation *sep = NULL;
	fz_context *ctx = xref->ctx;
	pdf_obj *nameobj = pdf_array_get(array, 1);
	pdf_obj *baseobj = pdf_array_get(array, 2);
	pdf_obj *tintobj = pdf_array_get(array, 3);
	fz_colorspace *base;
	pdf_function *tint = NULL;
	int n;

	fz_var(tint);
	fz_var(sep);

	if (pdf_is_array(nameobj))
		n = pdf_array_len(nameobj);
	else
		n = 1;

	if (n > FZ_MAX_COLORS)
		fz_throw(ctx, "too many components in colorspace");

	base = pdf_load_colorspace(xref, baseobj);

	fz_try(ctx)
	{
		tint = pdf_load_function(xref, tintobj, n, base->n);


		sep = fz_malloc_struct(ctx, struct separation);
		sep->base = base;
		sep->tint = tint;

		cs = fz_new_colorspace(ctx, n == 1 ? "Separation" : "DeviceN", n);
		cs->to_rgb = separation_to_rgb;
		cs->free_data = free_separation;
		cs->data = sep;
		cs->size += sizeof(struct separation) + (base ? base->size : 0) + pdf_function_size(tint);
	}
	fz_catch(ctx)
	{
		fz_drop_colorspace(ctx, base);
		pdf_drop_function(ctx, tint);
		fz_free(ctx, sep);
		fz_rethrow(ctx);
	}

	return cs;
}
