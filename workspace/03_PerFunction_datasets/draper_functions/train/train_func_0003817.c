P_Get_Property (Object w, Object prop, Object type, Object start,
                              Object len, Object deletep) {
    Atom req_type = AnyPropertyType, actual_type;
    int format;
    unsigned long nitems, bytes_left;
    unsigned char *data;
    Object ret, t, x;
    register unsigned int i;
    GC_Node2;

    Check_Type (w, T_Window);
    Check_Type (prop, T_Atom);
    if (!EQ(type, False)) {
        Check_Type (type, T_Atom);
        req_type = ATOM(type)->atom;
    }
    Check_Type (deletep, T_Boolean);
    Disable_Interrupts;
    if (XGetWindowProperty (WINDOW(w)->dpy, WINDOW(w)->win, ATOM(prop)->atom,
            Get_Long (start), Get_Long (len),
            EQ(deletep, True), req_type, &actual_type, &format,
            &nitems, &bytes_left, &data) != Success)
        Primitive_Error ("cannot get property");
    Enable_Interrupts;
    ret = t = P_Make_List (Make_Integer (4), Null);
    GC_Link2 (ret, t);
    x = Make_Atom (actual_type);
    Car (t) = x; t = Cdr (t);
    x = Make_Integer (format);
    Car (t) = x; t = Cdr (t);
    if (nitems) {
        if (format == 8) {
            Object s;
            x = Make_String ((char *)0, (int)nitems);
            s = Car (t) = x;
            memcpy (STRING(s)->data, (char *)data, (int)nitems);
        } else {
            Object v;
            GC_Node;
            v = Make_Vector ((int)nitems, Null);
            GC_Link (v);
            for (i = 0; i < nitems; i++) {
                x = Make_Unsigned (format == 16 ?
                    *((int16_t *)data + i) : *((int32_t *)data + i));
                VECTOR(v)->data[i] = x;
            }
            Car (t) = v;
            GC_Unlink;
        }
    }
    t = Cdr (t);
    x = Make_Unsigned_Long (bytes_left);
    Car (t) = x;
    GC_Unlink;
    return ret;
}
