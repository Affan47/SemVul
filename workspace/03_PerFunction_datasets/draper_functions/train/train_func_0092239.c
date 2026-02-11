pdf_extgstate_uses_blending(fz_context *ctx, pdf_obj *dict)
{
	pdf_obj *obj = pdf_dict_gets(dict, "BM");
	if (pdf_is_name(obj) && strcmp(pdf_to_name(obj), "Normal"))
		return 1;
	return 0;
}
