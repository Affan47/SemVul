AsnListAdd PARAMS((list),
AsnList* list )
{
    AsnListNode* newNode;
    void*      dataAddr;

    if( list->curr )
        {
	newNode  = (AsnListNode *) Asn1Alloc( sizeof(AsnListNode) + list->dataSize );
	dataAddr = (void *) &(newNode->data);

	newNode->next = list->curr->next;
	newNode->prev = list->curr;
	if( list->curr->next )
	    list->curr->next->prev = newNode;
	else
	    list->last = newNode;
	list->curr->next = newNode;

	list->curr = newNode;
	list->count++;
	}

    else
	dataAddr = NULL;

    return( dataAddr );
}
