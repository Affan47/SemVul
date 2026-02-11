gre_e_h(GWindow gw, GEvent *event) {
    if ( event->type==et_close ) {
	GRE *gre = GDrawGetUserData(gw);
	GRE_DoCancel(gre);
    } else if ( event->type == et_char ) {
return( false );
    }
return( true );
}
