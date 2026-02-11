xmms_collection_dag_restore (xmms_coll_dag_t *dag)
{
	xmmsv_coll_t *coll = NULL;
	xmms_medialib_session_t *session;
	xmmsv_t *cmdval;
	const gchar *query;
	GList *res;
	gint previd;

	session = xmms_medialib_begin ();


	query = "SELECT op.id AS id, lbl.name AS label, "
	        "       lbl.namespace AS nsid, op.type AS type "
	        "FROM CollectionOperators AS op, CollectionLabels as lbl "
	        "WHERE op.id=lbl.collid "
	        "ORDER BY id";
	res = xmms_medialib_select (session, query, NULL);

	previd = -1;

	while (res) {
		gint id, type, nsid;
		const gchar *label;

		cmdval = (xmmsv_t*) res->data;
		id = value_get_dict_int (cmdval, "id");
		type = value_get_dict_int (cmdval, "type");
		nsid = value_get_dict_int (cmdval, "nsid");
		label = value_get_dict_string (cmdval, "label");


		if (previd < 0 || id != previd) {
			coll = xmms_collection_dbread_operator (session, id, type);
			previd = id;
		}
		else {
			xmmsv_coll_ref (coll);
		}

		xmms_collection_dag_replace (dag, nsid, g_strdup (label), coll);

		xmmsv_unref (cmdval);
		res = g_list_delete_link (res, res);
	}

	xmms_medialib_end (session);


	xmms_collection_apply_to_all_collections (dag, bind_all_references, NULL);
}
