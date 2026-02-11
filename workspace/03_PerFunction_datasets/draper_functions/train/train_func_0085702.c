arrayObjectMatch(Objects *oa1, Objects *oa2)
{
    if (oa1 == oa2)
        return 1;
    if (oa1->dim != oa2->dim)
        return 0;
    for (size_t j = 0; j < oa1->dim; j++)
    {   RootObject *o1 = (*oa1)[j];
        RootObject *o2 = (*oa2)[j];
        if (!match(o1, o2))
        {
            return 0;
        }
    }
    return 1;
}
