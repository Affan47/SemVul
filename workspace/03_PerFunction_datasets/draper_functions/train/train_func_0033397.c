GME_StringChoices(GMatrixEdit *gme,GEvent *event,int r,int c) {
    GMenuItem *mi = gme->col_data[c].enum_vals;
    char *val = gme->data[r*gme->cols+c].u.md_str;
    int i;

    if ( gme->col_data[c].me_type==me_stringchoicetag ) {
	char buf[8];
	for ( i=0; mi[i].ti.text!=NULL || mi[i].ti.line || mi[i].ti.image!=NULL; ++i ) {
	    buf[0] = ((intpt) mi[i].ti.userdata)>>24;
	    buf[1] = ((intpt) mi[i].ti.userdata)>>16;
	    buf[2] = ((intpt) mi[i].ti.userdata)>>8;
	    buf[3] = ((intpt) mi[i].ti.userdata)&0xff;
	    buf[4] = '\0';
	    mi[i].ti.selected = mi[i].ti.checked = !gme->wasnew && val!=NULL &&
		    strcmp(buf,val)==0;
	}
    } else if ( gme->col_data[c].me_type==me_stringchoicetrans ) {
	for ( i=0; mi[i].ti.text!=NULL || mi[i].ti.line || mi[i].ti.image!=NULL; ++i )
	    mi[i].ti.selected = mi[i].ti.checked = !gme->wasnew && val!=NULL &&
		    strcmp((char *) mi[i].ti.userdata,val)==0;
    }
    if ( gme->col_data[c].enable_enum!=NULL )
	(gme->col_data[c].enable_enum)(&gme->g,mi,r,c);
    _GMenuCreatePopupMenu(gme->nested,event, mi, GME_FinishChoice);
}
