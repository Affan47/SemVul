arrayTypeCompatibleWithoutCasting(Loc loc, Type *t1, Type *t2)
{
    t1 = t1->toBasetype();
    t2 = t2->toBasetype();

    if ((t1->ty == Tarray || t1->ty == Tsarray || t1->ty == Tpointer) &&
        t2->ty == t1->ty)
    {
        if (t1->nextOf()->implicitConvTo(t2->nextOf()) >= MATCHconst ||
            t2->nextOf()->implicitConvTo(t1->nextOf()) >= MATCHconst)
            return 1;
    }
    return 0;
}
