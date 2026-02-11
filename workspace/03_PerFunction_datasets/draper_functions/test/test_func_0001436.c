on_run_complete (GObject *source,
                 GAsyncResult *result,
                 gpointer user_data)
{
	RunClosure *closure = user_data;
	g_return_if_fail (closure->result == NULL);
	closure->result = g_object_ref (result);
	g_main_loop_quit (closure->loop);
}
