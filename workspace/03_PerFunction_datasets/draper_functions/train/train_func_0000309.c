say_datetime(struct ast_channel *chan, time_t t, const char *ints, const char *lang)
{
	if (!strncasecmp(lang, "en", 2)) {
		return ast_say_datetime_en(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "de", 2)) {
		return ast_say_datetime_de(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "fr", 2)) {
		return ast_say_datetime_fr(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "ge", 2)) {
		static int deprecation_warning = 0;
		if (deprecation_warning++ % 10 == 0) {
			ast_log(LOG_WARNING, "ge is not a standard language code.  Please switch to using ka instead.\n");
		}
		return ast_say_datetime_ka(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "gr", 2)) {
		return ast_say_datetime_gr(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "he", 2)) {
		return ast_say_datetime_he(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "hu", 2)) {
		return ast_say_datetime_hu(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "ka", 2)) {
		return ast_say_datetime_ka(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "nl", 2)) {
		return ast_say_datetime_nl(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "pt_BR", 5)) {
		return ast_say_datetime_pt_BR(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "pt", 2)) {
		return ast_say_datetime_pt(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "th", 2)) {
		return ast_say_datetime_th(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "tw", 2)) {
		static int deprecation_warning = 0;
		if (deprecation_warning++ % 10 == 0) {
			ast_log(LOG_WARNING, "tw is a standard language code for Twi, not Taiwanese.  Please switch to using zh_TW instead.\n");
		}
		return ast_say_datetime_zh(chan, t, ints, lang);
	} else if (!strncasecmp(lang, "zh", 2)) {
		return ast_say_datetime_zh(chan, t, ints, lang);
	}


	return ast_say_datetime_en(chan, t, ints, lang);
}
