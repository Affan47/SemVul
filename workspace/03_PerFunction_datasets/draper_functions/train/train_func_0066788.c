on_new_prompt_creates (GcrSystemPrompter *prompter,
                       gpointer user_data)
{
	g_return_val_if_fail (GCR_IS_SYSTEM_PROMPTER (prompter), NULL);
	return g_object_new (GCR_TYPE_MOCK_PROMPT, NULL);
}
