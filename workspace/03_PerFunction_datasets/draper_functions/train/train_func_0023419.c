test_child_watch_callback(
    pid_t pid,
    gint status,
    gpointer data)
{
    static int count = 0;
    gint expected_pid = GPOINTER_TO_INT(data);

    if (pid != expected_pid
	    || !WIFEXITED(status)
	    || WEXITSTATUS(status) != 13)
	test_child_watch_result = FALSE;
    else
	test_child_watch_result = TRUE;

    count++;
    if(count >= 2)
	g_main_loop_quit(test_child_watch_main_loop);
}
