read_utf16_str (int word_len, guint8 const *data)
{
	int i;
	gunichar2 *uni_text = g_alloca (word_len * sizeof (gunichar2));


	for (i = 0 ; i < word_len ; i++, data += 2)
		uni_text [i] = GSF_LE_GET_GUINT16 (data);

	return (guchar *)g_utf16_to_utf8 (uni_text, word_len, NULL, NULL, NULL);
}
