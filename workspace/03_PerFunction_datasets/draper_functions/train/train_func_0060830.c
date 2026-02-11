pdf_free_array(pdf_obj *obj)
{
	int i;

	for (i = 0; i < obj->u.a.len; i++)
		pdf_drop_obj(obj->u.a.items[i]);

	fz_free(obj->ctx, obj->u.a.items);
	fz_free(obj->ctx, obj);
}
