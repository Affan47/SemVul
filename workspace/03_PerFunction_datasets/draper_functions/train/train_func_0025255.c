ManagePalettesVis(GTopLevelD *td, int is_visible ) {
    GTopLevelD *palette;

    if ( td->w!=last_paletted_focus_window )
return;
    for ( palette=td->palettes; palette!=NULL; palette = palette->nextp ) {
	if ( is_visible && palette->w->visible_request )
	    GDrawSetVisible(palette->w,true);
	else if ( !is_visible && palette->w->visible_request ) {
	    GDrawSetVisible(palette->w,false);
	    palette->w->visible_request = true;
	}
    }
}
