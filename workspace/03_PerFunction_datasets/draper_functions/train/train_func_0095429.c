setup_unlock_keyring_other (GkmWrapPrompt *self,
                            const gchar *label)
{
	GcrPrompt *prompt;
	const gchar *choice;
	gchar *text;

	g_assert (GKM_IS_WRAP_PROMPT (self));
	prompt = GCR_PROMPT (self);

	gcr_prompt_set_title (prompt, _("Unlock Keyring"));

	text = g_markup_printf_escaped (_("Enter password for keyring '%s' to unlock"), label);
	gcr_prompt_set_message (prompt, text);
	g_free (text);

	text = g_markup_printf_escaped (_("An application wants access to the keyring '%s', but it is locked"), label);
	gcr_prompt_set_description (prompt, text);
	g_free (text);

	choice = NULL;
	if (gkm_wrap_login_is_usable ())
		choice = _("Automatically unlock this keyring whenever I'm logged in");
	gcr_prompt_set_choice_label (prompt, choice);
	gcr_prompt_set_continue_label (prompt, _("Unlock"));
}
