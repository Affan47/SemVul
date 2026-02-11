forward_chars_with_skipping (GtkTextIter *iter,
			     gint         count,
			     gboolean     skip_invisible,
			     gboolean     skip_nontext,
			     gboolean     skip_decomp)
{
	gint i;

	g_return_if_fail (count >= 0);

	i = count;

	while (i > 0)
	{
		gboolean ignored = FALSE;

		if (skip_nontext && gtk_text_iter_get_char (iter) == GTK_TEXT_UNKNOWN_CHAR)
			ignored = TRUE;

		if (!ignored && skip_invisible &&
		     FALSE)
			ignored = TRUE;

		if (!ignored && skip_decomp)
		{


			gunichar *decomp;
			gsize decomp_len;
			decomp = g_unicode_canonical_decomposition (
				gtk_text_iter_get_char (iter), &decomp_len);
			i -= (decomp_len - 1);
			g_free (decomp);
		}

		gtk_text_iter_forward_char (iter);

		if (!ignored)
			--i;
	}
}
