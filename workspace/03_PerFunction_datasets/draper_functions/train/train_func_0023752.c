pqueue_find(pqueue_s *pq, unsigned char *prio64be)
	{
	pitem *next;
	pitem *found = NULL;

	if ( pq->items == NULL)
		return NULL;

	for ( next = pq->items; next->next != NULL; next = next->next)
		{
		if ( memcmp(next->priority, prio64be,8) == 0)
			{
			found = next;
			break;
			}
		}


	if ( memcmp(next->priority, prio64be,8) ==0)
		found = next;

	if ( ! found)
		return NULL;

#if 0
	if ( prev == NULL)
		pq->items = next->next;
	else
		prev->next = next->next;
#endif

	return found;
	}
