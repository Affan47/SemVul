GFI_LookupScrollbars(struct gfi_data *gfi, int isgpos, int refresh) {
    int lcnt, i,j;
    int width=0, wmax;
    GWindow gw = GDrawableGetWindow(GWidgetGetControl(gfi->gw,CID_LookupWin+isgpos));
    struct lkdata *lk = &gfi->tables[isgpos];
    GGadget *vsb = GWidgetGetControl(gfi->gw,CID_LookupVSB+isgpos);
    GGadget *hsb = GWidgetGetControl(gfi->gw,CID_LookupHSB+isgpos);
    int off_top, off_left;

    GDrawSetFont(gw,gfi->font);
    lcnt = 0;
    for ( i=0; i<lk->cnt; ++i ) {
	if ( lk->all[i].deleted )
    continue;
	++lcnt;
	wmax = GDrawGetBiText8Width(gw,lk->all[i].lookup->lookup_name,-1,-1,NULL);
	if ( wmax > width ) width = wmax;
	if ( lk->all[i].open ) {
	    for ( j=0; j<lk->all[i].subtable_cnt; ++j ) {
		if ( lk->all[i].subtables[j].deleted )
	    continue;
		++lcnt;
		wmax = gfi->fh+GDrawGetBiText8Width(gw,lk->all[i].subtables[j].subtable->subtable_name,-1,-1,NULL);
		if ( wmax > width ) width = wmax;
	    }
	}
    }
    width += gfi->fh;
    GScrollBarSetBounds(vsb,0,lcnt,(gfi->lkheight-2*LK_MARGIN)/gfi->fh);
    GScrollBarSetBounds(hsb,0,width,gfi->lkwidth-2*LK_MARGIN);
    off_top = lk->off_top;
    if ( off_top+((gfi->lkheight-2*LK_MARGIN)/gfi->fh) > lcnt )
	off_top = lcnt - (gfi->lkheight-2*LK_MARGIN)/gfi->fh;
    if ( off_top<0 )
	off_top  = 0;
    off_left = lk->off_left;
    if ( off_left+gfi->lkwidth-2*LK_MARGIN > width )
	off_left = width-(gfi->lkwidth-2*LK_MARGIN);
    if ( off_left<0 )
	off_left  = 0;
    if ( off_top!=lk->off_top || off_left!=lk->off_left ) {
	lk->off_top = off_top; lk->off_left = off_left;
	GScrollBarSetPos(vsb,off_top);
	GScrollBarSetPos(hsb,off_left);
	refresh = true;
    }
    if ( refresh )
	GDrawRequestExpose(gw,NULL,false);
}
