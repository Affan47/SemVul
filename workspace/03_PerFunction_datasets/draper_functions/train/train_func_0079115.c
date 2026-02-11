ajListReverse(AjPList list)
{
    AjPListNode head     = NULL;
    AjPListNode savenext = NULL;
    AjPListNode node     = NULL;

    if(!list)
        return;

    if(list->Count <= 1)
        return;

    head = list->Last;

    list->Last->Prev = list->First;

    for(node = list->First; node->Next; node = savenext)
    {
        savenext   = node->Next;
        node->Prev = node->Next;
        node->Next = head;
        head       = node;
    }

    list->First = head;

    list->First->Prev = NULL;

    return;
}
