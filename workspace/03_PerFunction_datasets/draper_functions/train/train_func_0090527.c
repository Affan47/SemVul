SetXi18nSelectionOwner(Xi18n i18n_core)
{
    Display *dpy = i18n_core->address.dpy;
    Window ims_win = i18n_core->address.im_window;
    Window root = RootWindow (dpy, DefaultScreen (dpy));
    Atom realtype;
    int realformat;
    unsigned long bytesafter;
    long *data=NULL;
    unsigned long length;
    Atom atom;
    int i;
    int found;
    int forse = False;
    char buf[256];

    (void)snprintf(buf, 256, "@server=%s", i18n_core->address.im_name);
    if ((atom = XInternAtom(dpy, buf, False)) == 0)
        return False;
    i18n_core->address.selection = atom;

    if (XIM_Servers == None)
        XIM_Servers = XInternAtom (dpy, XIM_SERVERS, False);

    XGetWindowProperty (dpy,
                        root,
                        XIM_Servers,
                        0L,
                        1000000L,
                        False,
                        XA_ATOM,
                        &realtype,
                        &realformat,
                        &length,
                        &bytesafter,
                        (unsigned char **) (&data));
    if (realtype != None && (realtype != XA_ATOM || realformat != 32)) {
        if (data != NULL)
            XFree ((char *) data);
        return False;
    }

    found = False;
    for (i = 0; i < length; i++) {
        if (data[i] == atom) {
            Window owner;
            found = True;
            if ((owner = XGetSelectionOwner (dpy, atom)) != ims_win) {
                if (owner == None  ||  forse == True)
                    XSetSelectionOwner (dpy, atom, ims_win, CurrentTime);
                else
                    return False;
            }
            break;
        }
    }

    if (found == False) {
        XSetSelectionOwner (dpy, atom, ims_win, CurrentTime);
        XChangeProperty (dpy,
                         root,
                         XIM_Servers,
                         XA_ATOM,
                         32,
                         PropModePrepend,
                         (unsigned char *) &atom,
                         1);
    }
    else {


        XChangeProperty (dpy,
                         root,
                         XIM_Servers,
                         XA_ATOM,
                         32,
                         PropModePrepend,
                         (unsigned char *) data,
                         0);
    }
    if (data != NULL)
        XFree ((char *) data);


    i18n_core->address.Localename = XInternAtom (dpy, LOCALES, False);
    i18n_core->address.Transportname = XInternAtom (dpy, TRANSPORT, False);
    return (XGetSelectionOwner (dpy, atom) == ims_win);
}
