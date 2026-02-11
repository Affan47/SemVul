Check_Formals (Object x, int *min, int *max) {
    Object s, t1, t2;

    *min = *max = 0;
    for (t1 = Car (x); !Nullp (t1); t1 = Cdr (t1)) {
        s = TYPE(t1) == T_Pair ? Car (t1) : t1;
        Check_Type (s, T_Symbol);
        for (t2 = Car (x); !EQ(t2, t1); t2 = Cdr (t2))
            if (EQ(s, Car (t2)))
                Primitive_Error ("~s: duplicate variable binding", s);
        if (TYPE(t1) != T_Pair)
            break;
        (*min)++; (*max)++;
    }
    if (TYPE(t1) == T_Symbol)
        *max = -1;
    else if (!Nullp (t1))
        Wrong_Type_Combination (t1, "list or symbol");
}
