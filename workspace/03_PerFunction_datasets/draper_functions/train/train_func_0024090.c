pdf_to_real(pdf_obj *obj)
{
	RESOLVE(obj);
	if (!obj)
		return 0;
	if (obj->kind == PDF_REAL)
		return obj->u.f;
	if (obj->kind == PDF_INT)
		return obj->u.i;
	return 0;
}
