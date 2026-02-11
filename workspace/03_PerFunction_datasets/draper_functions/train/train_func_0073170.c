ClearMacroList(GSList *gsl)
{
	MacroEvent *me;
	GSList * gslTemp=gsl;


	while(gslTemp!=NULL)
	{
		me=gslTemp->data;


		if(me->message==SCI_REPLACESEL ||
		   me->message==SCI_SEARCHNEXT ||
		   me->message==SCI_SEARCHPREV)
			g_free((void*)(me->lparam));

		g_free((void*)(gslTemp->data));
		gslTemp=g_slist_next(gslTemp);
	}


	g_slist_free(gsl);

	return NULL;
}
