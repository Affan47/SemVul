resolv_mux_done ( struct resolv_interface *resolv,
			      struct sockaddr *sa, int rc ) {
	struct resolv_mux *mux =
		container_of ( resolv, struct resolv_mux, child );


	resolv_unplug ( &mux->child );


	if ( rc == 0 ) {
		DBGC ( mux, "RESOLV %p succeeded using method %s\n",
		       mux, mux->resolver->name );
		goto finished;
	}


	mux->resolver++;
	if ( mux->resolver >= table_end ( RESOLVERS ) ) {
		DBGC ( mux, "RESOLV %p failed to resolve name\n", mux );
		goto finished;
	}
	if ( ( rc = resolv_mux_try ( mux ) ) != 0 )
		goto finished;


	return;

 finished:
	resolv_done ( &mux->parent, sa, rc );
}
