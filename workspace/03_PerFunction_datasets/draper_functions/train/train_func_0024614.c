add_hns_P()
{
	struct hns_P *head;
	int i;

	if(!HNS_P)
	{
		HNS_P = (struct hns_P*)mbkalloc(sizeof(struct hns_P)*64);
		FREE_HNS = addchain(FREE_HNS,HNS_P);

		for(i=0;i<=62;i++)
			HNS_P[i].NEXT=&(HNS_P[i+1]);
		HNS_P[63].NEXT=NULL;
	}
	head       = HNS_P;
	HNS_P      = HNS_P->NEXT;

	head->NEXT = NULL;
	head->idx  = 0;
    head->sig  = NULL;
	head->rcn  = 0;

	return(head);
}
