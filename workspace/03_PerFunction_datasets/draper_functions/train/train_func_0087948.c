setOpaque(unsigned char alpha) {
#ifdef HAVE_XRENDER
    static Atom m_alphaatom = XInternAtom(display(), "_NET_WM_WINDOW_OPACITY", False);
    unsigned int opacity = alpha << 24;
    changeProperty(m_alphaatom, XA_CARDINAL, 32, PropModeReplace, (unsigned char *) &opacity, 1l);
#endif
}
