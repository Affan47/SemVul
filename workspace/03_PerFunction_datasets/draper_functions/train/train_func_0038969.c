GetMacroEventFromString(gchar **s,gint *k)
{
	MacroEvent *me;

	me=g_new0(MacroEvent,1);

	me->message=strtoll(s[(*k)++],NULL,10);


	me->wparam=0;


	switch(me->message)
	{
		case SCI_SEARCHNEXT:
		case SCI_SEARCHPREV:

			me->lparam=(glong)(g_strcompress(s[(*k)++]));

			if((*((gchar*)(me->lparam)))==0)
			{
				g_free((gchar*)me->lparam);
				me->lparam=(glong)NULL;
			}


			me->wparam=strtoll(s[(*k)++],NULL,10);
			break;
		case SCI_REPLACESEL:

			me->lparam=(glong)(g_strcompress(s[(*k)++]));
			break;

		default:
			me->lparam=0;
			break;
	}


	return me;
}
