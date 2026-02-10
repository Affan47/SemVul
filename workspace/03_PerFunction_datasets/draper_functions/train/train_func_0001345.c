close_all_cb(GtkWidget *, gpointer data)
{
	GtkWidget *list = (GtkWidget *)data;

	if (list) {
		scope_entry *current = root_scope;

		while (current) {
			GDK_THREADS_LEAVE();
			if (current->sp) current->sp->stop();
			GDK_THREADS_ENTER();
			current = current->next;
		}
	}
}
