avdtp_reconfigure(struct avdtp *session, GSList *caps,
			struct avdtp_stream *stream)
{
	struct reconf_req *req;
	unsigned char *ptr;
	int caps_len, err;
	GSList *l;
	struct avdtp_service_capability *cap;

	if (!g_slist_find(session->streams, stream))
		return -EINVAL;

	if (stream->lsep->state != AVDTP_STATE_OPEN)
		return -EINVAL;


	for (l = caps, caps_len = 0; l != NULL; l = g_slist_next(l)) {
		cap = l->data;
		caps_len += cap->length + 2;
	}

	req = g_malloc0(sizeof(struct reconf_req) + caps_len);

	req->acp_seid = stream->rseid;


	for (l = caps, ptr = req->caps; l != NULL; l = g_slist_next(l)) {
		cap = l->data;
		memcpy(ptr, cap, cap->length + 2);
		ptr += cap->length + 2;
	}

	err = send_request(session, FALSE, stream, AVDTP_RECONFIGURE, req,
						sizeof(*req) + caps_len);
	g_free(req);

	return err;
}
