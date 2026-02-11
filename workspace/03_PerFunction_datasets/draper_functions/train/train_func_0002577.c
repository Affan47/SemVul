EntFindOrder(Entity *ent) {
    int ret;

    while ( ent!=NULL ) {
	if ( ent->type == et_splines ) {
	    ret = SPLFindOrder(ent->u.splines.splines);
	    if ( ret!=-1 )
return( ret );
	}
	ent = ent->next;
    }
return( -1 );
}
