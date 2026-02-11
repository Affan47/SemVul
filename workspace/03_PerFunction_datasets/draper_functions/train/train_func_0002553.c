e_text_model_get_nth_object_bounds (ETextModel *model,
                                    gint n,
                                    gint *start,
                                    gint *end)
{
	const gchar *txt = NULL, *obj = NULL;
	gint len = 0;

	g_return_if_fail (E_IS_TEXT_MODEL (model));

	txt = e_text_model_get_text (model);
	obj = e_text_model_get_nth_object (model, n, &len);

	g_return_if_fail (obj != NULL);

	if (start)
		*start = g_utf8_pointer_to_offset (txt, obj);
	if (end)
		*end = (start ? *start : 0) + len;
}
