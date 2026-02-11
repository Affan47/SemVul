rootwinPropertyNotify(int screen_num, Atom atom) {
    if (!FbTk::Transparent::haveRender())
        return false;

    checkAtoms();
    for (size_t i = 0; i < sizeof(root_props)/sizeof(RootProps); ++i) {
        if (root_props[i].atom == atom) {
            Pixmap root_pm = None;
            Atom real_type;
            int real_format;
            unsigned long items_read, items_left;
            unsigned long *data;

            if (XGetWindowProperty(display(),
                                   RootWindow(display(), screen_num),
                                   root_props[i].atom,
                                   0l, 1l,
                                   False, XA_PIXMAP,
                                   &real_type, &real_format,
                                   &items_read, &items_left,
                                   (unsigned char **) &data) == Success) {
                if (real_format == 32 && items_read == 1) {
                    root_pm = (Pixmap) (*data);
                }
                XFree(data);
                if (root_pm != None)
                    return setRootPixmap(screen_num, root_pm);
            }
            return false;
        }
    }
    return false;
}
