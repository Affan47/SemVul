e_text_model_get_nth_object (ETextModel *model,
                             gint n,
                             gint *len)
{
	ETextModelClass *class;

	g_return_val_if_fail (E_IS_TEXT_MODEL (model), NULL);

	if (n < 0 || n >= e_text_model_object_count (model))
		return NULL;

	class = E_TEXT_MODEL_GET_CLASS (model);

	if (class->get_nth_obj == NULL)
		return NULL;

	return class->get_nth_obj (model, n, len);
}
