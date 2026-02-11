LinkDccClient(struct DccUser *dccptr)

{
	dccptr->prev = NULL;
	dccptr->next = connections;
	if (dccptr->next)
		dccptr->next->prev = dccptr;
	connections = dccptr;

	Network->TotalConns++;
}
