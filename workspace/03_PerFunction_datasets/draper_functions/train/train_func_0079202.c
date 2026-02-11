P_Set_Size_Hints (Object w, Object a, Object h) {
    unsigned long mask;

    Check_Type (w, T_Window);
    Check_Type (a, T_Atom);
    memset ((char *)&SZH, 0, sizeof (SZH));
    mask = Vector_To_Record (h, Size_Hints_Size, Sym_Size_Hints,
        Size_Hints_Rec);
    if ((mask & (PPosition|USPosition)) == (PPosition|USPosition))
        mask &= ~PPosition;
    if ((mask & (PSize|USSize)) == (PSize|USSize))
        mask &= ~PSize;
    SZH.flags = mask;
    XSetWMSizeHints (WINDOW(w)->dpy, WINDOW(w)->win, &SZH, ATOM(a)->atom);
    return Void;
}
