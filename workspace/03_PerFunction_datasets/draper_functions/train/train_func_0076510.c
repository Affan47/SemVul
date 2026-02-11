setDND(bool enabled) {
    if (fDND != enabled) {
        fDND = enabled;

        if (fDND) {
            XChangeProperty(xapp->display(), handle(),
                            XA_XdndAware, XA_ATOM,
                            32, PropModeReplace,
                            (const unsigned char *)&XdndCurrentVersion, 1);
        } else {
            XDeleteProperty(xapp->display(), handle(), XA_XdndAware);
        }
    }
}
