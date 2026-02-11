InputRedirection(struct inputRedirect *input,GWindow gw) {
    GWindow ret;

    if ( input==NULL || input->cur_dlg->is_dying )
return( NULL );
    if ( gw->is_toplevel && ((GXWindow) gw)->not_restricted )
return( NULL );
    if ( GDrawWindowIsAncestor(input->cur_dlg,gw))
return( NULL );
    if ( input->it == it_restricted || input->it == it_redirected ) {
	if ( input->it == it_redirected )
return( input->cur_dlg );
	else
return( (GWindow) -1 );
    }
    if ( GDrawWindowIsAncestor(input->inactive,gw))
return( input->cur_dlg );
    ret = NULL;
    if ( input->prev!=NULL )
	ret = InputRedirection(input->prev,gw);
    if ( ret==NULL || ret==(GWindow) (-1) )
return( ret );
    if ( GDrawWindowIsAncestor(input->inactive,ret))
return( input->cur_dlg );

return( ret );
}
