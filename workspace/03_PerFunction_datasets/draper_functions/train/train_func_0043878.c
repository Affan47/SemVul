window_delete_event_cb (glWindow      *window,
			GdkEvent      *event,
			gpointer       user_data)
{
	gl_debug (DEBUG_WINDOW, "START");

	g_return_val_if_fail (window && GL_IS_WINDOW (window), TRUE);

	gl_file_close (window);

	gl_debug (DEBUG_WINDOW, "END");

	return TRUE;
}
