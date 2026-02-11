xmms_collection_client_query_infos (xmms_coll_dag_t *dag, xmmsv_coll_t *coll,
                                    gint32 lim_start, gint32 lim_len, xmmsv_t *order,
                                    xmmsv_t *fetch, xmmsv_t *group, xmms_error_t *err)
{
	GList *res = NULL;
	GString *query;


	if (xmmsv_list_get_size (fetch) == 0) {
		xmms_error_set (err, XMMS_ERROR_INVAL, "fetch list must not be empty!");
		return NULL;
	}


	if (!check_string_list (order)) {
		xmms_error_set (err, XMMS_ERROR_NOENT, "invalid order list!");
		return NULL;
	}
	if (!check_string_list (fetch)) {
		xmms_error_set (err, XMMS_ERROR_NOENT, "invalid fetch list!");
		return NULL;
	}
	if (!check_string_list (group)) {
		xmms_error_set (err, XMMS_ERROR_NOENT, "invalid group list!");
		return NULL;
	}


	if (!xmms_collection_validate (dag, coll, NULL, NULL)) {
		if (err) {
			xmms_error_set (err, XMMS_ERROR_INVAL, "invalid collection structure");
		}
		return NULL;
	}

	g_mutex_lock (dag->mutex);

	query = xmms_collection_get_query (dag, coll, lim_start, lim_len,
	                                   order, fetch, group);

	g_mutex_unlock (dag->mutex);

	XMMS_DBG ("COLLECTIONS: query_infos with %s", query->str);


	xmms_medialib_session_t *session = xmms_medialib_begin ();
	res = xmms_medialib_select (session, query->str, err);
	xmms_medialib_end (session);

	g_string_free (query, TRUE);

	return res;
}
