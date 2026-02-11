gcr_system_prompter_new_prompt_acculmulator (GSignalInvocationHint *ihint,
                                             GValue *return_accu,
                                             const GValue *handler_return,
                                             gpointer user_data)
{
	if (g_value_get_object (handler_return) != NULL) {
		g_value_copy (handler_return, return_accu);
		return FALSE;
	}

	return TRUE;
}
