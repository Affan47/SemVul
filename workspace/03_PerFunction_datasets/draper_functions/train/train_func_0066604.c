etc_dispose (GObject *object)
{
	ETableCol *etc = E_TABLE_COL (object);

	g_clear_object (&etc->spec);

	if (etc->ecell)
		g_object_unref (etc->ecell);
	etc->ecell = NULL;

	if (etc->pixbuf)
		g_object_unref (etc->pixbuf);
	etc->pixbuf = NULL;

	g_free (etc->text);
	etc->text = NULL;

	g_free (etc->icon_name);
	etc->icon_name = NULL;


	G_OBJECT_CLASS (e_table_col_parent_class)->dispose (object);
}
