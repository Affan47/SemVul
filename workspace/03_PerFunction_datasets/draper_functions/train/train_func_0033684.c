matcher_init(void)
{
	if (context_str[CONTEXT_SUBJECT] != NULL)
		return;

	context_str[CONTEXT_SUBJECT] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("Subject:"));
	context_str[CONTEXT_FROM] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("From:"));
	context_str[CONTEXT_TO] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("To:"));
	context_str[CONTEXT_CC] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("Cc:"));
	context_str[CONTEXT_NEWSGROUPS] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("Newsgroups:"));
	context_str[CONTEXT_IN_REPLY_TO] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("In-Reply-To:"));
	context_str[CONTEXT_REFERENCES] = g_strdup_printf(_("%s header"), prefs_common_translated_header_name("References:"));
	context_str[CONTEXT_HEADER] = g_strdup(_("header"));
	context_str[CONTEXT_HEADER_LINE] = g_strdup(_("header line"));
	context_str[CONTEXT_BODY_LINE] = g_strdup(_("body line"));
	context_str[CONTEXT_TAG]  = g_strdup(_("tag"));
}
