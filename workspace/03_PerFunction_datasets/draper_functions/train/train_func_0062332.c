save_picture(gamine_t *cb)
{
    struct stat st;
    gchar *dirname;
    gchar *filename;
    char buf[20];
    time_t timestamp;
    struct tm * t;
    timestamp = time(NULL);
    t = localtime(&timestamp);

    dirname = g_build_filename(g_get_home_dir(), "gamine", NULL);

    if(stat(dirname,&st) != 0)
        if (mkdir(dirname, 0750) < 0)
            printf(gettext("*** error: failed to create directory %s***\n"),
                    dirname);
    sprintf(buf,"%d-%d-%d_%d-%d-%d.png",1900 + t->tm_year,
            t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    filename = g_build_filename(dirname, buf, NULL);
    if (cairo_surface_write_to_png(cb->surface, filename) < 0)
        printf(gettext("*** error: failed to create file %s***\n"), filename);
}
