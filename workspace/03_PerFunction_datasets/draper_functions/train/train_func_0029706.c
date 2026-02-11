handle_property_notify(event_t *ev)
{
    D_EVENTS(("handle_property_notify(ev [%8p] on window 0x%08x)\n", ev, ev->xany.window));

#ifdef PIXMAP_OFFSET
    if (background_is_trans()) {
        Window win;
        Pixmap pmap;

        if ((ev->xany.window == TermWin.parent) || (ev->xany.window == Xroot)) {
            D_EVENTS(("On %s.  prop (_WIN_WORKSPACE) == 0x%08x, ev->xproperty.atom == 0x%08x\n",
                      ((ev->xany.window == Xroot) ? "the root window" : "TermWin.parent"), (int) props[PROP_DESKTOP],
                      (int) ev->xproperty.atom));
            if (ev->xproperty.atom == props[PROP_DESKTOP]) {
                win = get_desktop_window();
                if (win == (Window) 1) {

                    return 1;
                }

                if (desktop_window == None) {
                    free_desktop_pixmap();
                    FOREACH_IMAGE(if (image_mode_is(idx, MODE_TRANS)) {
                                  image_set_mode(idx, MODE_IMAGE); image_allow_mode(idx, ALLOW_IMAGE);}
                    );
                    return 1;
                }
                pmap = get_desktop_pixmap();
                if (pmap == (Pixmap) 1) {

                    return 1;
                }
                redraw_images_by_mode(MODE_TRANS | MODE_VIEWPORT);
                return 1;
            }
        }
        if (ev->xany.window == desktop_window) {
            D_EVENTS(("On desktop_window [0x%08x].  prop (_XROOTPMAP_ID) == %d, ev->xproperty.atom == %d\n",
                      (int) desktop_window, (int) props[PROP_TRANS_PIXMAP], (int) ev->xproperty.atom));
            if (ev->xproperty.atom == props[PROP_TRANS_PIXMAP]) {
                pmap = get_desktop_pixmap();
                if (pmap == (Pixmap) 1) {

                    return 1;
                }
                redraw_images_by_mode(MODE_TRANS | MODE_VIEWPORT);
                return 1;
            }
        }
    }
#endif
    if ((ev->xany.window == Xroot) && (image_mode_any(MODE_AUTO))) {
        D_EVENTS(("On the root window.  prop (ENLIGHTENMENT_COMMS) == %d, ev->xproperty.atom == %d\n", (int) props[PROP_ENL_COMMS],
                  (int) ev->xproperty.atom));
        if ((props[PROP_ENL_COMMS] != None) && (ev->xproperty.atom == props[PROP_ENL_COMMS])) {
            if ((enl_ipc_get_win()) != None) {
#ifdef PIXMAP_SUPPORT
                redraw_images_by_mode(MODE_AUTO);
#endif
            }
        }
    }
    if (ev->xany.window == TermWin.vt) {
        D_EVENTS(("PropertyNotify on term window for atom %d, state %d.  Selection atoms are %d and %d.\n", ev->xproperty.atom,
                  ev->xproperty.state, props[PROP_SELECTION_DEST], props[PROP_SELECTION_INCR]));
        if (ev->xproperty.atom == props[PROP_SELECTION_DEST] && ev->xproperty.state == PropertyNewValue) {
            D_SELECT(("Fetching next part of incremental selection.\n"));
            selection_fetch(ev->xproperty.window, ev->xproperty.atom, True);
        }
    }
    return 1;
}
