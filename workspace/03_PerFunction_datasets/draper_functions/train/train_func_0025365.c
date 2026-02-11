pdf_load_xobject(pdf_document *xref, pdf_obj *dict)
{
	pdf_xobject *form;
	pdf_obj *obj;
	fz_context *ctx = xref->ctx;

	if ((form = pdf_find_item(ctx, pdf_free_xobject_imp, dict)))
	{
		return form;
	}

	form = fz_malloc_struct(ctx, pdf_xobject);
	FZ_INIT_STORABLE(form, 1, pdf_free_xobject_imp);
	form->resources = NULL;
	form->contents = NULL;
	form->colorspace = NULL;
	form->me = NULL;
	form->iteration = 0;


	pdf_store_item(ctx, dict, form, pdf_xobject_size(form));

	obj = pdf_dict_gets(dict, "BBox");
	form->bbox = pdf_to_rect(ctx, obj);

	obj = pdf_dict_gets(dict, "Matrix");
	if (obj)
		form->matrix = pdf_to_matrix(ctx, obj);
	else
		form->matrix = fz_identity;

	form->isolated = 0;
	form->knockout = 0;
	form->transparency = 0;

	obj = pdf_dict_gets(dict, "Group");
	if (obj)
	{
		pdf_obj *attrs = obj;

		form->isolated = pdf_to_bool(pdf_dict_gets(attrs, "I"));
		form->knockout = pdf_to_bool(pdf_dict_gets(attrs, "K"));

		obj = pdf_dict_gets(attrs, "S");
		if (pdf_is_name(obj) && !strcmp(pdf_to_name(obj), "Transparency"))
			form->transparency = 1;

		obj = pdf_dict_gets(attrs, "CS");
		if (obj)
		{
			form->colorspace = pdf_load_colorspace(xref, obj);
			if (!form->colorspace)
				fz_throw(ctx, "cannot load xobject colorspace");
		}
	}

	form->resources = pdf_dict_gets(dict, "Resources");
	if (form->resources)
		pdf_keep_obj(form->resources);

	fz_try(ctx)
	{
		form->contents = pdf_keep_obj(dict);
	}
	fz_catch(ctx)
	{
		pdf_remove_item(ctx, pdf_free_xobject_imp, dict);
		pdf_drop_xobject(ctx, form);
		fz_throw(ctx, "cannot load xobject content stream (%d %d R)", pdf_to_num(dict), pdf_to_gen(dict));
	}
	form->me = pdf_keep_obj(dict);

	return form;
}
