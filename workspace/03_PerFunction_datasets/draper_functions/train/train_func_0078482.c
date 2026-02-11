P_Translate_Coordinates (Object src, Object x, Object y,
                                       Object dst) {
    int rx, ry;
    Window child;
    Object l, t, z;
    GC_Node3;

    Check_Type (src, T_Window);
    Check_Type (dst, T_Window);
    if (!XTranslateCoordinates (WINDOW(src)->dpy, WINDOW(src)->win,
            WINDOW(dst)->win, Get_Integer (x), Get_Integer (y), &rx, &ry,
            &child))
        return False;
    l = t = P_Make_List (Make_Integer (3), Null);
    GC_Link3 (l, t, dst);
    Car (t) = Make_Integer (rx); t = Cdr (t);
    Car (t) = Make_Integer (ry), t = Cdr (t);
    z = Make_Window (0, WINDOW(dst)->dpy, child);
    Car (t) = z;
    GC_Unlink;
    return l;
}
