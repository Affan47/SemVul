GWindowClearFocusGadgetOfWindow(GWindow gw) {
    GTopLevelD *td;
    if ( gw==NULL )
return;
    while ( gw->parent!=NULL && !gw->is_toplevel ) gw=gw->parent;
    td = (GTopLevelD *) (gw->widget_data);
    if ( gw == current_focus_window && td->gfocus!=NULL &&
	    td->gfocus->funcs->handle_focus!=NULL ) {
	GEvent e;
	e.type = et_focus;
	e.w = gw;
	e.u.focus.gained_focus = false;
	e.u.focus.mnemonic_focus = mf_normal;
	(td->gfocus->funcs->handle_focus)(td->gfocus,&e);
    }
    td->gfocus = NULL;
}
