Notification_Handler(GObject *obj,GeanyEditor *ed,SCNotification *nt,gpointer ud)
{
	MacroEvent *me;
	gint i;


	if(nt->nmhdr.code!=SCN_MACRORECORD)
		return FALSE;


	if(RecordingMacro==NULL)
		return FALSE;


	for(i=0;;i++)
	{

		if(nt->message==MacroDetails[i].message)
			break;


		if(MacroDetails[i].description==NULL)
		{
			dialogs_show_msgbox(GTK_MESSAGE_INFO,_("Unrecognised message\n%i %i %i"),nt->message,
			                    (gint)(nt->wParam),(gint)(nt->lParam));
			return FALSE;
		}

	}
	me=g_new0(MacroEvent,1);
	me->message=nt->message;
	me->wparam=nt->wParam;

	me->lparam=(me->message==SCI_SEARCHNEXT ||
	            me->message==SCI_SEARCHPREV ||
	            me->message==SCI_REPLACESEL)
		?((glong) g_strdup((gchar *)(nt->lParam))) : nt->lParam;


	RecordingMacro->MacroEvents=g_slist_prepend(RecordingMacro->MacroEvents,me);

	return FALSE;
}
