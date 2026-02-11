xmms_collection_dag_save (xmms_coll_dag_t *dag)
{
	gint i;
	xmms_medialib_session_t *session;

	session = xmms_medialib_begin_write ();


	xmms_medialib_select (session, "DELETE FROM CollectionAttributes", NULL);
	xmms_medialib_select (session, "DELETE FROM CollectionConnections", NULL);
	xmms_medialib_select (session, "DELETE FROM CollectionIdlists", NULL);
	xmms_medialib_select (session, "DELETE FROM CollectionLabels", NULL);
	xmms_medialib_select (session, "DELETE FROM CollectionOperators", NULL);


	coll_dbwrite_t dbinfos = { session, 1, 0 };
	for (i = 0; i < XMMS_COLLECTION_NUM_NAMESPACES; ++i) {
		dbinfos.nsid = i;
		xmms_collection_foreach_in_namespace (dag, i, dbwrite_operator, &dbinfos);
	}

	xmms_collection_foreach_in_namespace (dag, XMMS_COLLECTION_NSID_ALL,
	                                      dbwrite_strip_tmpprops, NULL);

	xmms_medialib_end (session);
}
