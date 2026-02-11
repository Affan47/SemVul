pdf_drop_obj(pdf_obj *obj)
{
	if (!obj)
		return;
	if (--obj->refs)
		return;
	if (obj->kind == PDF_ARRAY)
		pdf_free_array(obj);
	else if (obj->kind == PDF_DICT)
		pdf_free_dict(obj);
	else
		fz_free(obj->ctx, obj);
}
