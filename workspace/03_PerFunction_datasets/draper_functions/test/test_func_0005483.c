_GWidget_RemoveGadget(GGadget *g) {
    struct gwidgetcontainerdata *gd;
    GTopLevelD *td;
    GWindow gw = g->base;
    GGadget *next;

    if ( gw==NULL )
return;

    gd = (struct gwidgetcontainerdata *) (gw->widget_data);
    if ( gd==NULL || !gd->iscontainer )
	GDrawIError( "Attempt to remove a gadget to something which is not a container");
    if ( gd->gadgets==g )
	gd->gadgets = g->prev;
    else {
	for ( next = gd->gadgets; next!=NULL && next->prev!=g; next = next->prev );
	if ( next==NULL )
	    GDrawIError( "Attempt to remove a gadget which is not in the gadget list" );
	else
	    next->prev = g->prev;
    }
    if ( gd->grabgadget == g ) gd->grabgadget = NULL;
    g->prev = NULL;
    g->base = NULL;

    while ( gw->parent!=NULL && !gw->is_toplevel ) gw = gw->parent;
    td = (GTopLevelD *) (gw->widget_data);
    if ( td->gdef == g ) td->gdef = NULL;
    if ( td->gcancel == g ) td->gcancel = NULL;
    if ( td->gfocus == g ) td->gfocus = NULL;
}
