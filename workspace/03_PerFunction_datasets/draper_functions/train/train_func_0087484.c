FcRangeHash (const FcRange *r)
{
    FcRange c = FcRangeCanonicalize (r);
    int b = (int) (c.u.d.begin * 100);
    int e = FcDoubleCmpEQ (c.u.d.end, DBL_MAX) ? INT_MAX : (int) (c.u.d.end * 100);

    return b ^ (b << 1) ^ (e << 9);
}
