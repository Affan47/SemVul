G_get_default_window(struct Cell_head *window)
{
    char *err;

    if ((err = G__get_window(window, "", "DEFAULT_WIND", "PERMANENT"))) {
	G_fatal_error(_("default region %s"), err);
	G_free(err);
    }
    return 1;
}
