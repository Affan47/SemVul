ajListstrPopLast(AjPList list, AjPStr* Pstr)
{
    AjPListNode node = NULL;

    if(!list)
        return ajFalse;

    if(!list->Count)
        return ajFalse;

    node = list->Last->Prev;

    if(Pstr)
    {
        ajStrDel(Pstr);
        *Pstr = (AjPStr) listNodeItem(node);
    }

    if(list->Count == 1)
    {
        list->Last->Prev = NULL;

        if(listFreeNext >= listFreeMax)
            listFreeSetExpand();

        if(listFreeNext >= listFreeMax)
            AJFREE(list->First);
        else if(list->First)
            listFreeSet[listFreeNext++] = list->First;

        list->First = list->Last;
    }
    else
    {
        node->Prev->Next = list->Last;
        list->Last->Prev = node->Prev;

        if(listFreeNext >= listFreeMax)
            listFreeSetExpand();

        if(listFreeNext >= listFreeMax)
            AJFREE(node);
        else if(node)
        {
            listFreeSet[listFreeNext++] = node;
            node = NULL;
        }
    }

    --list->Count;

    return ajTrue;
}
