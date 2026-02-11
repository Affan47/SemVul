buildArrayLoop(Parameters *fparams)
{
    Type *tb = type->toBasetype();
    if (tb->ty == Tarray || tb->ty == Tsarray)
    {
        return e1->buildArrayLoop(fparams);
    }
    else
        return Expression::buildArrayLoop(fparams);
}
