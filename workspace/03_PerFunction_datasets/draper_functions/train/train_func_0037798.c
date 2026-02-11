stop_activity(struct dummy *dum)
{
	int i;


	dum->address = 0;


	for (i = 0; i < DUMMY_ENDPOINTS; ++i)
		nuke(dum, &dum->ep[i]);


}
