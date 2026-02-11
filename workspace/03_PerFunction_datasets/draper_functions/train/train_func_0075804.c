GRE_ImageChanged(GGadget *g, GEvent *e) {

    if ( e->type==et_controlevent && e->u.control.subtype == et_buttonactivate ) {
	GRE *gre = GDrawGetUserData(GGadgetGetWindow(g));
	GResImage **ri = GGadgetGetUserData(g);
	char *new;
	GImage *newi;
	GRect size;
	new = gwwv_open_filename_with_path("Find Image",
		(*ri)==NULL?NULL: (*ri)->filename,
		"*.{png,jpeg,jpg,tiff,bmp,xbm}",NULL,
		_GGadget_GetImagePath());
	if ( new==NULL )
return( true );
	newi = GImageRead(new);
	if ( newi==NULL ) {
	    gwwv_post_error(_("Could not open image"),_("Could not open %s"), new );
	    free( new );
	} else if ( *ri==NULL ) {
	    *ri = gcalloc(1,sizeof(GResImage));
	    (*ri)->filename = new;
	    (*ri)->image = newi;
	    GGadgetSetTitle8(g,"...");
	} else {
	    free( (*ri)->filename );
	    (*ri)->filename = new;
	    if ( !_GGadget_ImageInCache((*ri)->image ) )
		GImageDestroy((*ri)->image);
	    (*ri)->image = newi;
	}
	((GButton *) g)->image = newi;
	GGadgetGetDesiredSize(g,&size,NULL);
	GGadgetResize(g,size.width,size.height);
	GRE_RefreshAll(gre);
    }
return( true );
}
