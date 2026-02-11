debug_log_io_cb (GIOChannel  *io,
                 GIOCondition condition,
                 gpointer     data)
{
        char a;

        while (read (debug_log_pipes[0], &a, 1) != 1)
                ;

        ck_log_toggle_debug ();

        return TRUE;
}
