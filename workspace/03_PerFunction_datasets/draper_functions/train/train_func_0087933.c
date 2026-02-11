ndmp2_sxa_config_get_butype_attr (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	ndmp9_config_info *	ci = &sess->config_info;
	ndmp9_butype_info *	bu = 0;
	unsigned int		i;

	assert (xa->request.protocol_version == NDMP2VER);

      NDMS_WITH(ndmp2_config_get_butype_attr)
	ndmos_sync_config_info (sess);

	for (i = 0; i < ci->butype_info.butype_info_len; i++) {
		bu = &ci->butype_info.butype_info_val[i];

		if (strcmp (request->name, bu->butype_name) == 0) {
			break;
		}
	}

	if (i >= ci->butype_info.butype_info_len) {
		NDMADR_RAISE_ILLEGAL_ARGS("butype");
	}

	reply->attrs = bu->v2attr.value;

	return 0;
      NDMS_ENDWITH
}
