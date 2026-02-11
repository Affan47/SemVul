GMatrixEdit_Expose(GWindow pixmap, GGadget *g, GEvent *event) {
    GMatrixEdit *gme = (GMatrixEdit *) g;
    GRect r, old, older;
    int c, y, lastc;
    Color fg = gmatrixedit_title_fg;

    if ( gme->g.state!=gs_enabled )
	fg = gme->g.box->disabled_foreground;

    GBoxDrawBorder(pixmap,&g->r,g->box,g->state,false);
    if ( gme->has_titles ) {
	r = gme->g.inner;
	r.height = gme->font_fh;
	r.width = gme->hsb->r.width;
	GDrawPushClip(pixmap,&r,&older);
	GDrawFillRect(pixmap,&r,gmatrixedit_title_bg);
	y = r.y + gme->font_as;
	GDrawSetFont(pixmap,gme->titfont);
	for ( lastc = gme->cols-1; lastc>0 && gme->col_data[lastc].hidden; --lastc );
	for ( c=0; c<gme->cols; ++c ) {
	    if ( gme->col_data[c].title!=NULL &&
		    !gme->col_data[c].hidden ) {
		r.x = gme->col_data[c].x + gme->g.inner.x - gme->off_left;
		r.width = gme->col_data[c].width;
		GDrawPushClip(pixmap,&r,&old);
		GDrawDrawBiText8(pixmap,r.x,y,gme->col_data[c].title,-1,NULL,fg);
		GDrawPopClip(pixmap,&old);
	    }
	    if ( c!=lastc && !gme->col_data[c].hidden)
		GDrawDrawLine(pixmap,r.x+gme->col_data[c].width+gme->hpad/2,r.y,
				     r.x+gme->col_data[c].width+gme->hpad/2,r.y+r.height,
				     gmatrixedit_title_divider);
	}
	GDrawPopClip(pixmap,&older);
    }
return( true );
}
