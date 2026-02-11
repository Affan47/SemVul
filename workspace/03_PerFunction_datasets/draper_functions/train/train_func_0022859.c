Convert_Duration (gulong duration)
{
    guint hour=0;
    guint minute=0;
    guint second=0;
    gchar *data = NULL;

    if (duration == 0)
        return g_strdup_printf("%d:%.2d",minute,second);

    hour   = duration/3600;
    minute = (duration%3600)/60;
    second = (duration%3600)%60;

    if (hour)
        data = g_strdup_printf("%d:%.2d:%.2d",hour,minute,second);
    else
        data = g_strdup_printf("%d:%.2d",minute,second);

    return data;
}
