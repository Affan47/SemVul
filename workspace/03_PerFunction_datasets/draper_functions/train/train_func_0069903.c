Call1500E740(unsigned int nValue)
{
    THTreeItem * pItem1 = pItem3058;
    THTreeItem * pItem2;
    THTreeItem * pNext;
    THTreeItem * pPrev;
    THTreeItem ** ppItem;

    if(PTR_INVALID_OR_NULL(pItem1) || (pItem2 = pItem1) == NULL)
    {
        if((pItem2 = &items0008[nItems++]) != NULL)
            pItem1 = pItem2;
        else
            pItem1 = pFirst;
    }
    else
        pItem1 = pItem2;

    pNext = pItem1->next;
    if(pNext != NULL)
    {
        pPrev = pItem1->prev;
        if(PTR_INVALID_OR_NULL(pPrev))
            pPrev = PTR_NOT(pPrev);
        else
            pPrev += (pItem1 - pItem1->next->prev);

        pPrev->next = pNext;
        pNext->prev = pPrev;
        pItem1->next = NULL;
        pItem1->prev = NULL;
    }

    ppItem = &pFirst;
    if(nValue > 1)
    {

        pItem1->next = *ppItem;
        pItem1->prev = (*ppItem)->prev;

        (*ppItem)->prev = pItem2;
        *ppItem = pItem1;

        pItem2->parent = NULL;
        pItem2->child  = NULL;
    }
    else
    {
        pItem1->next = (THTreeItem *)ppItem;
        pItem1->prev = ppItem[1];

        pPrev = ppItem[1];
        if(PTR_INVALID_OR_NULL(pPrev))
        {
            pPrev = PTR_NOT(pPrev);
            pPrev->next = pItem1;
            pPrev->prev = pItem2;

            pItem2->parent = NULL;
            pItem2->child  = NULL;
        }
        else
        {
            if(PTR_INVALID(pItem305C))
                pPrev += (THTreeItem *)ppItem - (*ppItem)->prev;
            else
                pPrev += PTR_INT(pItem305C);

            pPrev->next    = pItem1;
            ppItem[1]      = pItem2;
            pItem2->parent = NULL;
            pItem2->child  = NULL;
        }
    }
    return pItem2;
}
