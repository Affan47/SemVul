outlet_new(t_object *owner, t_symbol *s)
{
    t_outlet *x = (t_outlet *)getbytes(sizeof(*x)), *y, *y2;
    x->o_owner = owner;
    x->o_next = 0;
    if (y = owner->ob_outlet)
    {
        while (y2 = y->o_next) y = y2;
        y->o_next = x;
    }
    else owner->ob_outlet = x;
    x->o_connections = 0;
    x->o_sym = s;
    return (x);
}
