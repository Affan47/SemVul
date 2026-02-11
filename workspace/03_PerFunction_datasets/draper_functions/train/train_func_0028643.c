set_unlock_options_on_prompt (GkmWrapPrompt *self, CK_ATTRIBUTE_PTR options, CK_ULONG n_options)
{
	gboolean chosen = FALSE;
	gboolean bval;

	g_assert (GKM_IS_WRAP_PROMPT (self));
	g_assert (options || !n_options);

	if (gkm_attributes_find_boolean (options, n_options, CKA_GNOME_TRANSIENT, &bval))
		chosen = bval;

	gcr_prompt_set_choice_chosen (GCR_PROMPT (self), chosen);
}
