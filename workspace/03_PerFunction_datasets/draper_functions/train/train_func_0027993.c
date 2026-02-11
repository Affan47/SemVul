pdf_run_Do(pdf_csi *csi, pdf_obj *rdb)
{
	fz_context *ctx = csi->dev->ctx;
	pdf_obj *dict;
	pdf_obj *obj;
	pdf_obj *subtype;

	dict = pdf_dict_gets(rdb, "XObject");
	if (!dict)
		fz_throw(ctx, "cannot find XObject dictionary when looking for: '%s'", csi->name);

	obj = pdf_dict_gets(dict, csi->name);
	if (!obj)
		fz_throw(ctx, "cannot find xobject resource: '%s'", csi->name);

	subtype = pdf_dict_gets(obj, "Subtype");
	if (!pdf_is_name(subtype))
		fz_throw(ctx, "no XObject subtype specified");

	if (pdf_is_hidden_ocg(pdf_dict_gets(obj, "OC"), csi, rdb))
		return;

	if (!strcmp(pdf_to_name(subtype), "Form") && pdf_dict_gets(obj, "Subtype2"))
		subtype = pdf_dict_gets(obj, "Subtype2");

	if (!strcmp(pdf_to_name(subtype), "Form"))
	{
		pdf_xobject *xobj;

		xobj = pdf_load_xobject(csi->xref, obj);


		if (!xobj->resources)
			xobj->resources = pdf_keep_obj(rdb);

		fz_try(ctx)
		{
			pdf_run_xobject(csi, xobj->resources, xobj, fz_identity);
		}
		fz_always(ctx)
		{
			pdf_drop_xobject(ctx, xobj);
		}
		fz_catch(ctx)
		{
			fz_throw(ctx, "cannot draw xobject (%d %d R)", pdf_to_num(obj), pdf_to_gen(obj));
		}
	}

	else if (!strcmp(pdf_to_name(subtype), "Image"))
	{
		if ((csi->dev->hints & FZ_IGNORE_IMAGE) == 0)
		{
			fz_image *img = pdf_load_image(csi->xref, obj);

			fz_try(ctx)
			{
				pdf_show_image(csi, img);
			}
			fz_always(ctx)
			{
				fz_drop_image(ctx, img);
			}
			fz_catch(ctx)
			{
				fz_rethrow(ctx);
			}
		}
	}

	else if (!strcmp(pdf_to_name(subtype), "PS"))
	{
		fz_warn(ctx, "ignoring XObject with subtype PS");
	}

	else
	{
		fz_throw(ctx, "unknown XObject subtype: '%s'", pdf_to_name(subtype));
	}
}
