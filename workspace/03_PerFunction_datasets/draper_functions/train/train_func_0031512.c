altalldequeue(Alt *a)
{
	int i;

	for(i=0; a[i].op!=CHANEND && a[i].op!=CHANNOBLK; i++)
		if(a[i].op != CHANNOP)
			altdequeue(&a[i]);
}
