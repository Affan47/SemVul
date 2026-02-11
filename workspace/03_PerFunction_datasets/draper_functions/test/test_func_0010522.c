catargs (arr)
    ESTRUC_
        *arr;
{
    register size_t
        count;
    ESTRUC_
        *ep,
        e;

    if (!(count = arr->type))
        return;

    ep = (ESTRUC_ *)arr->code;

    e = ep[--count];

    while (count--)
        catcode(&e, &ep[count]);

    free(arr->code);
    *arr = e;
}
