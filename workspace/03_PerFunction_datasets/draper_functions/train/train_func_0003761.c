getNetWMDesktopHint(long *workspace) {
    *workspace = 0;

    if (!prop.net_wm_desktop)
        return false;

    Atom r_type;
    int r_format;
    unsigned long count;
    unsigned long bytes_remain;
    unsigned char *prop;

    if (XGetWindowProperty(xapp->display(),
                           handle(),
                           _XA_NET_WM_DESKTOP,
                           0, 1, False, XA_CARDINAL,
                           &r_type, &r_format,
                           &count, &bytes_remain, &prop) == Success && prop)
    {
        if (r_type == XA_CARDINAL && r_format == 32 && count == 1U) {
            long ws = *(long *)prop;
            if (ws < workspaceCount) {
                *workspace = ws;
                XFree(prop);
                return true;
            }
        }
        XFree(prop);
    }
    return false;
}
