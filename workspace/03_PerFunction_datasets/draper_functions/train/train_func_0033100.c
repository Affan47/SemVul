constConv(Type *to)
{
    if (to->ty == Tsarray)
    {
        TypeSArray *tsa = (TypeSArray *)to;
        if (!dim->equals(tsa->dim))
            return MATCHnomatch;
    }
    return TypeNext::constConv(to);
}
