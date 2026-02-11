gcr_prompt_get_caller_window (GcrPrompt *prompt)
{
	gchar *caller_window = NULL;
	g_return_val_if_fail (GCR_IS_PROMPT (prompt), NULL);
	g_object_get (prompt, "caller-window", &caller_window, NULL);
	return caller_window;
}
