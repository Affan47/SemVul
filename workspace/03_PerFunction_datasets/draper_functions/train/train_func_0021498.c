P_Reverse (Object x) {
    Object ret;
    GC_Node;

    GC_Link (x);
    for (ret = Null; !Nullp (x); x = Cdr (x)) {
        Check_List (x);
        ret = Cons (Car (x), ret);
    }
    GC_Unlink;
    return ret;
}
