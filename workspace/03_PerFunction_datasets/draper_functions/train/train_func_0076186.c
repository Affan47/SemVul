pdf_new_rect(fz_context *ctx, fz_rect *rect)
{
	pdf_obj *arr = NULL;
	pdf_obj *item = NULL;

	fz_var(arr);
	fz_var(item);
	fz_try(ctx)
	{
		arr = pdf_new_array(ctx, 4);

		item = pdf_new_real(ctx, rect->x0);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, rect->y0);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, rect->x1);
		pdf_array_push(arr, item);
		pdf_drop_obj(item);
		item = NULL;

		item = pdf_new_real(ctx, rect->y1);
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
