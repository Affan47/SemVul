e_text_model_changed (ETextModel *model)
{
	ETextModelClass *class;

	g_return_if_fail (E_IS_TEXT_MODEL (model));

	class = E_TEXT_MODEL_GET_CLASS (model);


	if (class->objectify != NULL)
		class->objectify (model);

	g_signal_emit (model, signals[E_TEXT_MODEL_CHANGED], 0);
}
