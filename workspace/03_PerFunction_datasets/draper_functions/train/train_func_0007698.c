gtk_column_chooser_init(GTypeInstance *instance, gpointer unused_g_class)
{
    GtkColumnChooser *cc;

	g_return_if_fail(instance != NULL);
	(void) unused_g_class;

	cc = (GtkColumnChooser *) instance;
    cc->widget = NULL;
    cc->col_map = htable_create(HASH_KEY_SELF, 0);
    cc->closed = FALSE;
}
