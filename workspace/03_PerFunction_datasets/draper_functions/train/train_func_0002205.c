ev_desktop_names(FbEv *ev, gpointer p)
{
    ENTER;
    if (ev->desktop_names) {
        g_strfreev (ev->desktop_names);
        ev->desktop_names = NULL;
    }
    RET();
}
