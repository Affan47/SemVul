mud_log_close(MudLog *log)
{
    gchar buf[255];
    time_t t;

    if(log->priv->logfile == NULL)
        return;

    time(&t);
    strftime(buf, 255,
            _("\n *** Log stops *** %d/%m/%Y %H:%M:%S\n"),
            localtime(&t));

    fprintf(log->priv->logfile, "%s", buf);
    fclose(log->priv->logfile);

    log->priv->active = FALSE;
}
