vListInsert( xList *pxList, xListItem *pxNewListItem )
{
volatile xListItem *pxIterator;
portTickType xValueOfInsertion;


	xValueOfInsertion = pxNewListItem->xItemValue;


	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{


		for( pxIterator = ( xListItem * ) &( pxList->xListEnd ); pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext )
		{


		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = ( volatile xListItem * ) pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = ( volatile xListItem * ) pxNewListItem;


	pxNewListItem->pvContainer = ( void * ) pxList;

	( pxList->uxNumberOfItems )++;
}
