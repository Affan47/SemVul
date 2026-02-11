ajListPeekLast(const AjPList list, void** Pitem)
{
    AjPListNode rest = NULL;

    if(!list)
        return ajFalse;

    if(!list->Count)
        return ajFalse;

    if(list->Last)
        rest = list->Last->Prev;
    else
        rest = list->First;

    if(Pitem)
        *Pitem = listNodeItem(rest);

    return ajTrue;
}
