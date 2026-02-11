resetServer(struct display *d)
{
    if (dpy && (d->displayType & d_origin) != dFromXDMCP)
        pseudoReset();
}
