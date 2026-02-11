ajListstrToarray(const AjPList list, AjPStr** array)
{
    ajulong i = 0UL;
    ajulong n = 0UL;

    AjPListNode rest = NULL;

    n = list->Count;
    rest = list->First;

    if(!n)
    {
        *array = NULL;

        return 0UL;
    }

    *array = AJALLOC((size_t) (n + 1) * sizeof(array));

    for(i = 0UL; i < n; i++)
    {
        (*array)[i] = (AjPStr) rest->Item;
        rest = rest->Next;
    }

    (*array)[n] = (AjPStr) NULL;

    return n;
}
