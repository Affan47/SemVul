on_new_prompt_not_called (GcrSystemPrompter *prompter,
                          gpointer user_data)
{
	g_return_val_if_fail (GCR_IS_SYSTEM_PROMPTER (prompter), NULL);
	g_return_val_if_reached (NULL);
}
