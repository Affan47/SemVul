printRings(gint nRings, GList** rings)
{
	gint i;
	for(i=0;i<nRings;i++)
	{
		GList* glist = rings[i];
		GList* l = NULL;
		if(ringsSize[i]<ringSizeMin) continue;
		printf("Ring number %d : ",i+1);
		for(l=glist; l != NULL; l = l->next)
			printf("%d ",1+GPOINTER_TO_INT(l->data));
		printf("\n");
	}
}
