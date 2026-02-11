General_Map (int argc, Object *argv, register int accum) {
    register int i;
    Object *args;
    Object head, list, tail, cell, arglist, val;
    GC_Node2; GCNODE gcv;
    TC_Prolog;
    Alloca_Begin;

    Check_Procedure (argv[0]);
    Alloca (args, Object*, (argc-1) * sizeof (Object));
    list = tail = Null;
    GC_Link2 (list, tail);
    gcv.gclen = argc; gcv.gcobj = args; gcv.next = &gc2; GC_List = &gcv;
    while (1) {
        for (i = 1; i < argc; i++) {
            head = argv[i];
            if (Nullp (head)) {
                GC_Unlink;
                Alloca_End;
                return list;
            }
            Check_Type (head, T_Pair);
            args[i-1] = Car (head);
            argv[i] = Cdr (head);
        }
        arglist = P_List (argc-1, args);
        TC_Disable;
        val = Funcall (argv[0], arglist, 0);
        TC_Enable;
        if (!accum)
            continue;
        cell = Cons (val, Null);
        if (Nullp (list))
            list = cell;
        else
            (void)P_Set_Cdr (tail, cell);
        tail = cell;
    }

}
