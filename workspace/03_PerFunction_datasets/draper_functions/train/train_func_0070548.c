ajListPushlist(AjPList list, AjPList* Plist)
{
    AjPList more = *Plist;

    if(more->Count)
    {

        if(list->Count)
        {

            more->Last->Item = list->First->Item;
            more->Last->Next = list->First->Next;
            list->First->Next->Prev = more->Last;
        }
        else
        {

            list->Last = more->Last;
        }

        if(listFreeNext >= listFreeMax)
            listFreeSetExpand();

        if(listFreeNext >= listFreeMax)
            AJFREE(list->First);
        else if(list->First)
            listFreeSet[listFreeNext++] = list->First;

        list->First = more->First;
        list->Count += more->Count;
        list->First->Prev = NULL;
        more->First = NULL;
        more->Count=0;

#ifdef AJ_SAVESTATS
        if(list->Count > listMaxNum)
            listMaxNum = list->Count;
#endif
    }

    ajListFree(Plist);

    return;
}
