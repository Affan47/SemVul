ints(int low, int up)
{
    if (low > up) {
        return(nil);
    } else {
        return(small_cons(small_cons(INT_TO_SEXPR(low), nil), ints(low+1, up)));
    }
}
