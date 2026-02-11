isPointerCmpExp(Expression *e, Expression **p1, Expression **p2)
{
    int ret = 1;
    while (e->op == TOKnot)
    {   ret *= -1;
        e = ((NotExp *)e)->e1;
    }
    switch(e->op)
    {
    case TOKlt:
    case TOKle:
        ret *= -1;

    case TOKgt:
    case TOKge:
        *p1 = ((BinExp *)e)->e1;
        *p2 = ((BinExp *)e)->e2;
        if ( !(isPointer((*p1)->type) && isPointer((*p2)->type)) )
            ret = 0;
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}
