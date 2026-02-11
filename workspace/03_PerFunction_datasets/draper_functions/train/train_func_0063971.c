gmlHugeSetChild( struct huge_parent *pParent,
                            struct huge_href *pItem )
{

    struct huge_child *pChild = pParent->pFirst;
    while( pChild != NULL )
    {
         if( pChild->psChild == pItem->psNode )
         {
            pChild->pItem = pItem;
            return TRUE;
         }
         pChild = pChild->pNext;
    }
    return FALSE;
}
