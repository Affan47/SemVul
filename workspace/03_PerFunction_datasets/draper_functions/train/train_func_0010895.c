pdf_new_array(fz_context *ctx, int initialcap)
{
	pdf_obj *obj;
	int i;

	obj = Memento_label(fz_malloc(ctx, sizeof(pdf_obj)), "pdf_obj(array)");
	obj->ctx = ctx;
	obj->refs = 1;
	obj->kind = PDF_ARRAY;

	obj->u.a.len = 0;
	obj->u.a.cap = initialcap > 1 ? initialcap : 6;

	fz_try(ctx)
	{
		obj->u.a.items = Memento_label(fz_malloc_array(ctx, obj->u.a.cap, sizeof(pdf_obj*)), "pdf_obj(array items)");
	}
	fz_catch(ctx)
	{
		fz_free(ctx, obj);
		fz_rethrow(ctx);
	}
	for (i = 0; i < obj->u.a.cap; i++)
		obj->u.a.items[i] = NULL;

	return obj;
}
