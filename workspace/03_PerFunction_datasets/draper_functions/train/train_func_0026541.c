GTextInfoGetAs(GWindow base,GTextInfo *ti, FontInstance *font) {
    int fh=0, as=0, ds=0, ld;
    int iheight=0;
    int height;
    GTextBounds bounds;

    GDrawWindowFontMetrics(base,font,&as, &ds, &ld);
    if ( ti->text!=NULL ) {
	GDrawSetFont(base,font);
	GDrawGetBiTextBounds(base,ti->text, -1, NULL, &bounds);
	if ( as<bounds.as ) as = bounds.as;
	if ( ds<bounds.ds ) ds = bounds.ds;
    }
    fh = as+ds;
    if ( ti->image!=NULL ) {
	iheight = GImageGetScaledHeight(base,ti->image);
    }
    if ( (height = fh)<iheight ) height = iheight;

    if ( ti->text!=NULL )
return( as+(height>fh?(height-fh)/2:0) );

return( iheight );
}
