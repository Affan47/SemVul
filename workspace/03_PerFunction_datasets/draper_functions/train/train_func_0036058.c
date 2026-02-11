Get_Long (Object x) {
    double d;
    int expo;

    switch (TYPE(x)) {
    case T_Fixnum:
        return FIXNUM(x);
    case T_Bignum:
        return Bignum_To_Long (x);
    case T_Flonum:
        d = FLONUM(x)->val;
        if (d != floor (d))
            Wrong_Type (x, T_Fixnum);
        (void)frexp (d, &expo);
        if (expo <= 8 * (int)sizeof(long) - 1)
            return d;
        Primitive_Error ("integer out of range: ~s", x);
    default:
        Wrong_Type (x, T_Fixnum);
    }

}
