prompt_handler(const gchar *log_domain, GLogLevelFlags log_level,
                           const gchar *message, gpointer data)
{
    if (ob_state() == OB_STATE_RUNNING && allow_prompts)
        prompt_queue = g_list_prepend(prompt_queue, g_strdup(message));
    else
        log_handler(log_domain, log_level, message, data);
}
