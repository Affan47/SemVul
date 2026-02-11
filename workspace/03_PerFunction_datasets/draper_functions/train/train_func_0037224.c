_GWidget_ClearGrabGadget(GGadget *g) {
    struct gwidgetcontainerdata *gd=NULL;
    GWindow gw = g->base;

    if ( gw!=NULL )
        gd = (struct gwidgetcontainerdata *) (gw->widget_data);
    if ( gd==NULL || !gd->iscontainer )
        GDrawIError( "This gadget isn't in a container, can't be a grab gadget" );
    else
        gd->grabgadget = NULL;
}
