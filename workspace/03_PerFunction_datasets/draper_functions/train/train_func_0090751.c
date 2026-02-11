list_free( LIST	*head )
{


	if( head )
	{
	    head->tail->next = freelist;
	    freelist = head;
	}
}
