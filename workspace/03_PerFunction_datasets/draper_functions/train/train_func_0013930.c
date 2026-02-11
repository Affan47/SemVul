pdf_pattern_uses_blending(fz_context *ctx, pdf_obj *dict)
{
	pdf_obj *obj;
	obj = pdf_dict_gets(dict, "Resources");
	if (pdf_resources_use_blending(ctx, obj))
		return 1;
	obj = pdf_dict_gets(dict, "ExtGState");
	return pdf_extgstate_uses_blending(ctx, obj);
}
