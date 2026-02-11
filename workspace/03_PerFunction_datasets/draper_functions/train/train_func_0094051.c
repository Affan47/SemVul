config_set_default (void) {
    FILE* fh = 0;
    if (! (fh = fopen (config_filename, "w")))
        slog (L_FATAL, "can't open config for writing... abort\n");

    fwrite (config_str, strlen (config_str), 1, fh);
    fclose (fh);
    config_load ();
}
