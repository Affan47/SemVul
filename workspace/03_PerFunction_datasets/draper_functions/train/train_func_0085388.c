P_Atom_Name (Object d, Object a) {
    register char *s;

    Check_Type (d, T_Display);
    Check_Type (a, T_Atom);
    Disable_Interrupts;
    s = XGetAtomName (DISPLAY(d)->dpy, ATOM(a)->atom);
    Enable_Interrupts;
    return Make_String (s, strlen (s));
}
