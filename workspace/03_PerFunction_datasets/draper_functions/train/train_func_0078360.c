SSHasDrawn(SplineSet *ss) {
    while ( ss!=NULL ) {
	if ( !ss->is_clip_path )
return( true );
	ss = ss->next;
    }
return( false );
}
