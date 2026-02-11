ei_big_comp(erlang_big *x, erlang_big *y)
{
    if ( x->is_neg == y->is_neg ) {
        int c = I_comp(x->digits,(x->arity+1)/2,y->digits,(y->arity+1)/2);
        if ( x->is_neg )
            return -c;
        else
            return c;
    } else {
        return x->is_neg ? -1 : 1;
    }
}
