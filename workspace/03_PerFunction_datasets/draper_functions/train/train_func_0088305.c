Named_Let (Object argl) {
    Object b, val, tail, vlist, vtail, flist, ftail, cell;
    GC_Node6;
    TC_Prolog;

    tail = vlist = vtail = flist = ftail = Null;
    GC_Link6 (argl, tail, vlist, vtail, flist, ftail);
    TC_Disable;
    for (tail = Car (Cdr (argl)); !Nullp (tail); tail = Cdr (tail)) {
        Check_List (tail);
        b = Car (tail);
        if (Nullp (b))
            Primitive_Error ("bad binding form");
        val = P_Cdr (b);
        Check_List (val);
        if (Nullp (val) || !Nullp (Cdr (val)))
            Primitive_Error ("bad binding form");
        Check_Type (Car (b), T_Symbol);
        if (!Nullp (val))
            val = Car (val);
        cell = Cons (val, Null);
        if (Nullp (flist))
            flist = cell;
        else
            (void)P_Set_Cdr (ftail, cell);
        ftail = cell;
        cell = Cons (Car (Car (tail)), Null);
        if (Nullp (vlist))
            vlist = cell;
        else
            (void)P_Set_Cdr (vtail, cell);
        vtail = cell;
    }

    Push_Frame (Add_Binding (Null, Car (argl), Null));
    tail = Cons (vlist, Cdr (Cdr (argl)));
    if (Nullp (Cdr (tail)))
        Primitive_Error ("no subexpressions in named let");
    tail = P_Lambda (tail);
    COMPOUND(tail)->name = Car (argl);
    b = Lookup_Symbol (Car (argl), 1);
    Cdr (b) = tail;
    SYMBOL(Car (argl))->value = tail;
    TC_Enable;

    Pop_Frame ();


    tail = Funcall (tail, flist, 1);
    GC_Unlink;
    return tail;
}
