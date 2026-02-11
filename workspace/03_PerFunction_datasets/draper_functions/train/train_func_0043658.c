snprint_wm_name(char *buf, size_t len, Window w)
{
    char *n;

    if ((n = get_wm_name(w))) {
        if (get_wm_state(w) == NormalState) {
            if (snprintf(buf, len, "%s", n) > len)
                strcpy(buf+len-4, "...");
        } else {
            if (snprintf(buf, len, "[%s]", n) > len)
                strcpy(buf+len-5, "...]");
        }
        XFree(n);
    } else {
        snprintf(buf, len, "%#lx", w);
    }
}
