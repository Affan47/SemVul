after_put_esv (ExcelStyleVariant *esv, gboolean was_added, gint index,
	       gpointer user)
{
	if (was_added) {
		;
	} else {
		g_free (esv);
	}
}
