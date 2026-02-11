oflib_preview_e_h(GWindow gw, GEvent *event) {
    OFLibDlg *d = GDrawGetUserData(gw);

    if ( event->type==et_resize ) {
	GRect size;
	GDrawGetSize(gw,&size);
	d->pheight = size.height; d->pwidth = size.width;
	if ( d->preview_image!=NULL ) {
	    GGadget *hsb = GWidgetGetControl(d->gw,CID_PreviewHSB);
	    GGadget *vsb = GWidgetGetControl(d->gw,CID_PreviewVSB);
	    GScrollBarSetBounds(hsb,0,GImageGetWidth(d->preview_image),d->pwidth);
	    GScrollBarSetBounds(vsb,0,GImageGetHeight(d->preview_image),d->pheight);
	}
    } else if ( event->type==et_expose && d->preview_image ) {
	GRect src;
	GRect *exp = &event->u.expose.rect;
	src.x = d->p_off_left+exp->x; src.y = d->p_off_top+exp->y;
	src.width = d->pwidth-exp->x; src.height = d->pheight-exp->y;
	src.width = GImageGetWidth(d->preview_image)-exp->x;
	src.height = GImageGetHeight(d->preview_image)-exp->y;
	if ( src.width>exp->width )
	    src.width = exp->width;
	if ( src.height>exp->height )
	    src.height = exp->height;
	GDrawDrawImage(gw,d->preview_image,&src,exp->x,exp->y);
    }
return( true );
}
