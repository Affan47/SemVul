MakeContainerWidget(GWindow gw) {
    struct gwidgetcontainerdata *gd;

    if ( gw->widget_data!=NULL )
	GDrawIError( "Attempt to make a window into a widget twice");
    if ( !widgets_initted )
	gwidget_init();
    if ( gw->parent==NULL || gw->is_toplevel )
	gd = gcalloc(1,sizeof(struct gtopleveldata));
    else
	gd = gcalloc(1,sizeof(struct gwidgetcontainerdata));
    gw->widget_data = (struct gwidgetdata *) gd;
    gd->w = gw;
    gd->e_h = gw->eh;
    gw->eh = _GWidget_Container_eh;
    gd->enabled = true;
    gd->iscontainer = true;
    gd->funcs = &_gwidget_container_funcs;
    if ( gw->parent!=NULL && !gw->is_toplevel ) {
	if ( gw->parent->widget_data==NULL )
	    MakeContainerWidget(gw->parent);
	if ( !gw->parent->widget_data->iscontainer )
	    GDrawIError( "Attempt to add a widget to something which is not a container");
	gd->next = ((struct gwidgetcontainerdata *) (gw->parent->widget_data))->widgets;
	((struct gwidgetcontainerdata *) (gw->parent->widget_data))->widgets =
		(struct gwidgetdata *) gd;
    } else {
	struct gtopleveldata *topd;
	topd = (struct gtopleveldata *) gd;
	gd->funcs = &_gwidget_toplevel_funcs;
	gw->eh = _GWidget_TopLevel_eh;
	topd->handle_key = _GWidget_TopLevel_Key;
	topd->istoplevel = true;
    }
}
