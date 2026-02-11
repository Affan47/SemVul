save_defaults(void)
{
    char path[MAX_BUF],buf[MAX_BUF];
    FILE *fp;
    int i;

    snprintf(path, sizeof(path), "%s/.crossfire/gdefaults2", getenv("HOME"));
    CONVERT_FILESPEC_TO_OS_FORMAT(path);
    if (make_path_to_file(path)==-1) {
        LOG(LOG_ERROR, "config.c::save_defaults","Could not create %s", path);
        return;
    }
    if ((fp=fopen(path,"w"))==NULL) {
        LOG(LOG_ERROR, "config.c::save_defaults", "Could not open %s", path);
        return;
    }
    fprintf(fp,"# crossfire-client-gtk2 automatically generates this file.\n");
    fprintf(fp,"# Manual editing is allowed, but the client may be a bit\n");
    fprintf(fp,"# finicky about the keys and values.  Comparisons are case\n");
    fprintf(fp,"# sensitive.  'True' and 'False' are the proper case, but\n");
    fprintf(fp,"# have been replaced with 1 and 0 respectively.\n#\n");
    fprintf(fp,"server: %s\n", server);
    fprintf(fp,"theme: %s\n", theme);
    fprintf(fp,"faceset: %s\n", face_info.want_faceset);
    fprintf(fp,"window_layout: %s\n", window_xml_file);


    for (i=1; i < CONFIG_NUMS; i++) {
        fprintf(fp,"%s: %d\n", config_names[i], want_config[i]);
    }

    fclose(fp);
    snprintf(buf, sizeof(buf), "Defaults saved to %s",path);
    draw_ext_info(NDI_BLUE, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_CONFIG, buf);
}
