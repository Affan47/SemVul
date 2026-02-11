P_Set_After_Function (Object d, Object f) {
    Object old;

    Check_Type (d, T_Display);
    if (EQ(f, False)) {
        (void)XSetAfterFunction (DISPLAY(d)->dpy, (int (*)())0);
    } else {
        Check_Procedure (f);
        (void)XSetAfterFunction (DISPLAY(d)->dpy, X_After_Function);
    }
    old = DISPLAY(d)->after;
    DISPLAY(d)->after = f;
    return old;
}
