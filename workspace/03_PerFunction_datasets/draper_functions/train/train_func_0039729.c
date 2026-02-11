mame_process_exited (GvaProcess *process, gint status)
{
        if (WIFEXITED (status))
                g_log (
                        G_LOG_DOMAIN, GVA_DEBUG_MAME,
                        "Process %d exited with status %d",
                        gva_process_get_pid (process),
                        WEXITSTATUS (status));
}
