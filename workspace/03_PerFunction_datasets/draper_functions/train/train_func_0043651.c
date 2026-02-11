charset_to_utf8 (std::string text, std::string charset,
						   guint retries)
{
	gchar *utf8 = NULL;
	if (!charset.empty())
		utf8 = g_convert (text.c_str(), -1, "utf-8", charset.c_str(), 0,0,0);
	else
		utf8 = g_locale_to_utf8 (text.c_str(), -1, 0, 0, 0);


	if (!utf8 && retries)
		return charset_to_utf8 (text.substr (0, text.size()-1), charset,
								retries - 1);


	if (!utf8) {
		gchar *tmp = g_strdup_printf (_("[Cannot convert character sets "
										"(from \"%s\" to \"utf-8\")]"),
									  charset.empty() ? "C" : charset.c_str());
		utf8 = g_locale_to_utf8 (tmp, -1, 0, 0, 0);
		g_free (tmp);
	}

	return utf8;
}
