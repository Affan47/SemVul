popup_eh(GWindow popup,GEvent *event) {
    GGadget *owner = GDrawGetUserData(popup);

    if ( event->type == et_controlevent ) {
	GList *gl = (GList *) (event->u.control.g);
	void (*inform)(GGadget *,int) = (void (*) (GGadget *,int)) GGadgetGetUserData(&gl->g);
	int i;
	for ( i=0; i<gl->ltot; ++i )
	    if ( gl->ti[i]->selected )
	break;
	if ( i>=gl->ltot ) i = -1;
	GDrawDestroyWindow(popup);
	(inform)(owner,i);
    } else if ( event->type == et_close ) {
	GGadget *g = GWindowGetFocusGadgetOfWindow(popup);
	void (*inform)(GGadget *,int) = (void (*) (GGadget *,int)) GGadgetGetUserData(g);
	GDrawDestroyWindow(popup);
	_GWidget_ClearPopupOwner(owner);
	_GWidget_ClearGrabGadget(owner);
	(inform)(owner,-1);
    } else if ( event->type == et_destroy ) {
	_GWidget_ClearPopupOwner(owner);
	_GWidget_ClearGrabGadget(owner);
    }
return( true );
}
