config_clear_section (const char * section)
{
    g_return_if_fail (defaults && keyfile);
    pthread_mutex_lock (& mutex);

    if (! section)
        section = DEFAULT_SECTION;

    if (g_key_file_has_group (keyfile, section))
    {
        g_key_file_remove_group (keyfile, section, NULL);
        modified = TRUE;
    }

    pthread_mutex_unlock (& mutex);
}
