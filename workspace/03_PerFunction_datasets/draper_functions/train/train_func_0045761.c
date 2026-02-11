l2l_e_h(GWindow gw, GEvent *event) {

    if ( event->type==et_close ) {
	L2LDlg *d = GDrawGetUserData(gw);
	d->done = true;
    } else if ( event->type == et_char ) {
return( false );
    }
return( true );
}
