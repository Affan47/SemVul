buildArrayLoop(Parameters *fparams)
{
    switch(op)
    {
    case TOKadd:
    case TOKmin:
    case TOKmul:
    case TOKdiv:
    case TOKmod:
    case TOKxor:
    case TOKand:
    case TOKor:
#if DMDV2
    case TOKpow:
#endif
    {


        BinExp *e = (BinExp *)copy();
        e->e1 = e->e1->buildArrayLoop(fparams);
        e->e2 = e->e2->buildArrayLoop(fparams);
        e->type = NULL;
        return e;
    }
    default:
        return Expression::buildArrayLoop(fparams);
    }
}
