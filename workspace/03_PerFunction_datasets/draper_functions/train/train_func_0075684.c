Call1500E820(THTreeItem * pItem)
{
    THTreeItem * pItem1;
    THTreeItem * pItem2 = NULL;
    THTreeItem * pItem3;
    THTreeItem * pPrev;

    for(; pItem != NULL; pItem = pItem->parent)
    {
        pItem->byteValue++;

        for(pItem1 = pItem; ; pItem1 = pPrev)
        {
            pPrev = pItem1->prev;
            if(PTR_INVALID_OR_NULL(pPrev))
            {
                pPrev = NULL;
                break;
            }

            if(pPrev->byteValue >= pItem->byteValue)
                break;
        }

        if(pItem1 == pItem)
            continue;

        if(pItem1->next != NULL)
        {
            pItem2 = pItem1->GetPrevItem(-1);
            pItem2->next = pItem1->next;
            pItem1->next->prev = pItem1->prev;
            pItem1->next = NULL;
            pItem1->prev = NULL;
        }

        pItem2 = pItem->next;
        pItem1->next = pItem2;
        pItem1->prev = pItem2->prev;
        pItem2->prev = pItem1;
        pItem->next = pItem1;
        if((pItem2 = pItem1) != NULL)
        {
            pItem2 = pItem->GetPrevItem(-1);
            pItem2->next = pItem->next;
            pItem->next->prev = pItem->prev;
            pItem->next = NULL;
            pItem->prev = NULL;
        }

        if(pPrev == NULL)
            pPrev = PTR_PTR(&pFirst);

        pItem2       = pPrev->next;
        pItem->next  = pItem2;
        pItem->prev  = pItem2->prev;
        pItem2->prev = pItem;
        pPrev->next  = pItem;

        pItem3 = pItem1->parent->child;
        pItem2 = pItem->parent;
        if(pItem2->child == pItem)
            pItem2->child = pItem1;
        if(pItem3 == pItem1)
            pItem1->parent->child = pItem;

        pItem2 = pItem->parent;
        pItem->parent  = pItem1->parent;
        pItem1->parent = pItem2;
        offs0004++;
    }
}
