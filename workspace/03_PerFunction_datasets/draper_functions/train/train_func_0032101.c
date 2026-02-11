pdf_to_dict(pdf_obj *obj)
{
	RESOLVE(obj);
	return (obj && obj->kind == PDF_DICT ? obj : NULL);
}
