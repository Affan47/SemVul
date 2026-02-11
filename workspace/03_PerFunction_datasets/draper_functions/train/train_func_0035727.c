GeomDrawWireFrame(gdouble scaleBall)
{
	int i;
	int j;
	gboolean* Ok = NULL;
	GList* list = NULL;

	if(Ncenters>0) Ok = g_malloc(Ncenters*sizeof(gboolean));
	for(i = 0;i<Ncenters;i++) Ok[i] = FALSE;

	for(list=BondsOrb;list!=NULL;list=list->next)
	{
		BondType* data=(BondType*)list->data;
		i = data->n1;
		j = data->n2;
		if(!ShowHAtomOrb && (strcmp("H",GeomOrb[i].Symb)==0 || strcmp("H",GeomOrb[j].Symb)==0)) continue;
		if(data->bondType == GABEDIT_BONDTYPE_HYDROGEN)
			draw_wireframe(i,j,1);
		else
			 draw_wireframe(i,j, 2);
		Ok[i] = TRUE;
		Ok[j] = TRUE;
	}
	for(i = 0;i<Ncenters;i++)
	{
		if(!ShowHAtomOrb && strcmp("H",GeomOrb[i].Symb)==0) continue;
		if(!Ok[i]) draw_ball(i,0.2*scaleBall);
	}
	if(Ok) g_free(Ok);
	glLineWidth(1);

	return TRUE;
}
