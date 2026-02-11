resetSelectedBasis(Cbase *base, gboolean cont)
{
	gchar *AtomTypeBase[3];
	gchar *temp;
	Cbasetot *basetot;
	gint i;

	for(i=0;i<3;i++) AtomTypeBase[i] = g_malloc(40*sizeof(gchar));

	sscanf(base->TypeBase,"%s %s %s",AtomTypeBase[0],AtomTypeBase[1],AtomTypeBase[2]);

	temp=AtomTypeBase[0];
	AtomTypeBase[0]=AtomTypeBase[1];
	AtomTypeBase[1]=temp;

	basetot = get_base_total_from_path();
	if(!strstr(AtomTypeBase[0],"ECP"))
	{
        	if(cont) DefineTypeAll(basetot,AtomTypeBase,";c");
		else DefineTypeAll(basetot,AtomTypeBase,NULL);
 	}
	else DefineTypeAll(basetot,AtomTypeBase,NULL);


	set_base_total_from_path(basetot);

	for(i=0;i<3;i++) g_free(AtomTypeBase[i]);
}
