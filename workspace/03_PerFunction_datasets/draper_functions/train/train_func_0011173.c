xmms_medialib_num_not_resolved (xmms_medialib_session_t *session)
{
	gint ret;
	g_return_val_if_fail (session, 0);

	xmms_sqlite_query_int (session->sql, &ret,
	                       "SELECT COUNT(id) AS value FROM Media WHERE "
	                       "key='%s' AND intval IN (%d, %d) AND source=%d",
	                       XMMS_MEDIALIB_ENTRY_PROPERTY_STATUS,
	                       XMMS_MEDIALIB_ENTRY_STATUS_NEW,
	                       XMMS_MEDIALIB_ENTRY_STATUS_REHASH,
	                       XMMS_MEDIALIB_SOURCE_SERVER_ID);

	return ret;
}
