GWidgetChoicesBM8(char *title, const char **choices,char *sel,
	int cnt, char *buts[2], const char *question,...) {
    struct dlg_info d;
    GWindow gw;
    va_list ap;
    GGadget *list;
    GTextInfo **lsel;
    int i; int32 len;
    char *buttons[3];

    if ( screen_display==NULL )
return( -2 );

    if ( buts==NULL ) {
	buts = buttons;
	buttons[2] = NULL;
	if ( _ggadget_use_gettext ) {
	    buts[0] = _("_OK");
	    buts[1] = _("_Cancel");
	} else {
	    buts[0] = u2utf8_copy(GStringGetResource(_STR_OK,NULL));
	    buts[1] = u2utf8_copy(GStringGetResource(_STR_Cancel,NULL));
	}
    }
    va_start(ap,question);
    gw = ChoiceDlgCreate8(&d,title,question,ap,
	    choices,cnt,sel,buts,-1,true,false);
    va_end(ap);
    while ( !d.done )
	GDrawProcessOneEvent(NULL);
    if ( d.ret==-1 ) {
	for ( i=0; i<cnt; ++i )
	    sel[i] = 0;
    } else {
	list = GWidgetGetControl(gw,CID_List);
	lsel = GGadgetGetList(list,&len);
	for ( i=0; i<len; ++i )
	    sel[i] = lsel[i]->selected;
    }
    GDrawDestroyWindow(gw);
    GDrawSync(NULL);
    GDrawProcessPendingEvents(NULL);
    if ( !_ggadget_use_gettext ) {
	free(buts[0]); free(buts[1]);
    }
return(d.ret);
}
