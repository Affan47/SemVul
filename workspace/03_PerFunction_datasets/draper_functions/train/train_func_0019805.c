P_Abs (Object x) {
    register int i;

    Check_Number (x);
    switch (TYPE(x)) {
    case T_Fixnum:
        i = FIXNUM(x);
        return i < 0 ? Make_Integer (-i) : x;
    case T_Flonum:
        return Make_Flonum (fabs (FLONUM(x)->val));
    case T_Bignum:
        return Bignum_Abs (x);
    default:
        return Null;
    }

}
