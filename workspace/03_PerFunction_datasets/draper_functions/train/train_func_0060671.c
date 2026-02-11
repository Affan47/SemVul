abi_stock_from_toolbar_id (const gchar *toolbar_id)
{

	gchar 		 *stock_id = g_strdup (ABIWORD_STOCK_PREFIX);
	gchar		**tokens;
	gchar		**iter;
	gchar 		 *tmp1;
	const gchar	 *tmp2;
	gint	  	  off;

	tmp1 = g_ascii_strdown (toolbar_id, -1);

	static size_t underscorelen = 0;
	size_t tmp1len = strlen(tmp1);

	if (underscorelen == 0) {

		gchar *lastunderscore = g_strrstr_len(tmp1, tmp1len, "_");

		if (lastunderscore && *lastunderscore) {
			underscorelen = strlen(lastunderscore);
		} else {
			UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);


			underscorelen = 6;
		}
	}

	off = tmp1len - underscorelen;
	tmp1[off] = '\0';
	tokens = g_strsplit (tmp1, "_", 0);
	g_free (tmp1);

	iter = tokens;
	while (*iter) {
		tmp1 = stock_id;
		stock_id = g_strdup_printf ("%s-%s", stock_id, *iter);
		g_free (tmp1);
		iter++;
	}
	g_strfreev (tokens);

	tmp2 = abi_stock_get_gtk_stock_id (stock_id);
	if (tmp2) {
		g_free (stock_id);
		stock_id = g_strdup (tmp2);
	} else {
		xxx_UT_DEBUGMSG(("abi_stock_get_gtk_stock_id returned NULL for stock_id: %s\n", stock_id));
	}

	return stock_id;
}
