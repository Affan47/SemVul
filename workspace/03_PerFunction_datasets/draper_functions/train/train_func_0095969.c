camel_pop3_engine_command_new (CamelPOP3Engine *pe,
                               guint32 flags,
                               CamelPOP3CommandFunc func,
                               gpointer data,
                               GCancellable *cancellable,
                               GError **error,
                               const gchar *fmt,
                               ...)
{
	CamelPOP3Command *pc;
	va_list ap;

	g_return_val_if_fail (pe != NULL, NULL);

	pc = g_malloc0 (sizeof (*pc));
	pc->func = func;
	pc->func_data = data;
	pc->flags = flags;

	va_start (ap, fmt);
	pc->data = g_strdup_vprintf (fmt, ap);
	va_end (ap);
	pc->state = CAMEL_POP3_COMMAND_IDLE;
	pc->error_str = NULL;


	engine_command_queue (pe, pc, cancellable, error);

	return pc;
}
