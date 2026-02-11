P_List (int argc, Object *argv) {
    Object list, tail, cell;
    GC_Node2;

    GC_Link2 (list, tail);
    for (list = tail = Null; argc-- > 0; tail = cell) {
        cell = Cons (*argv++, Null);
        if (Nullp (list))
            list = cell;
        else
            (void)P_Set_Cdr (tail, cell);
    }
    GC_Unlink;
    return list;
}
