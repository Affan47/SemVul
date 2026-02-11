P_List_Tail (Object x, Object num) {
    register int n;

    for (n = Get_Exact_Integer (num); n > 0 && !Nullp (x); n--, x = P_Cdr (x))
        ;
    return x;
}
