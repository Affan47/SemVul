tds_srv_charset_changed_num(TDSSOCKET * tds, int canonic_charset_num)
{
	TDSICONV *char_conv = tds->char_convs[client2server_chardata];

	if (IS_TDS7_PLUS(tds) && canonic_charset_num == TDS_CHARSET_ISO_8859_1)
		canonic_charset_num = TDS_CHARSET_CP1252;

	tdsdump_log(TDS_DBG_FUNC, "setting server single-byte charset to \"%s\"\n", canonic_charsets[canonic_charset_num].name);

	if (canonic_charset_num == char_conv->server_charset.canonic)
		return;


	char_conv = tds_iconv_get_info(tds, tds->char_convs[client2ucs2]->client_charset.canonic, canonic_charset_num);
	if (char_conv)
		tds->char_convs[client2server_chardata] = char_conv;


	if (IS_TDS7_PLUS(tds))
		return;

	char_conv = tds->char_convs[iso2server_metadata];

	tds_iconv_info_close(char_conv);

	tds_iconv_info_init(char_conv, TDS_CHARSET_ISO_8859_1, canonic_charset_num);
}
