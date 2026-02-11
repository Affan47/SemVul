P_Close_Font (Object f) {
    Check_Type (f, T_Font);
    if (FONT(f)->id)
        XUnloadFont (FONT(f)->dpy, FONT(f)->id);
    FONT(f)->id = 0;
    Deregister_Object (f);
    return Void;
}
