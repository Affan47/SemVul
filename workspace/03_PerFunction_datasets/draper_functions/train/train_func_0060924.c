e_text_model_append (ETextModel *model,
                     const gchar *text)
{
	g_return_if_fail (E_IS_TEXT_MODEL (model));

	if (text == NULL)
		return;

	e_text_model_insert (model, e_text_model_get_text_length (model), text);
}
