GetMarkersUsed(ScintillaObject* sci)
{
	guint32 *markers;


	markers=(guint32*)(g_object_get_data(G_OBJECT(sci),"Geany_Numbered_Bookmarks_Used"));


	if(markers!=NULL)
		return markers;


	markers=g_malloc(sizeof(guint32));


	if(markers==NULL)
		return NULL;


	(*markers)=0;


	g_object_set_data(G_OBJECT(sci),"Geany_Numbered_Bookmarks_Used",(gpointer)markers);

	return markers;
}
