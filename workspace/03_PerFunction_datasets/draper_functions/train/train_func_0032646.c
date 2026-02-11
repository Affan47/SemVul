pdf_new_matrix(fz_context *ctx, fz_matrix *mtx)
{
	pdf_obj *arr = NULL;
	pdf_obj *item = NULL;

	fz_var(arr);
	fz_var(item);
	fz_try(ctx)
	{
		arr = pdf_new_array(ctx, 6);

		item = pdf_new_real(ctx, mtx->a);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, mtx->b);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, mtx->c);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, mtx->d);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, mtx->e);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, mtx->f);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;
	}
	fz_catch(ctx)
	{
		pdf_drop_obj(item);
		pdf_drop_obj(arr);
		fz_rethrow(ctx);
	}

	return arr;
}
