ndmp_sxa_config_get_auth_attr (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
      NDMS_WITH(ndmp9_config_get_auth_attr)
	switch (request->auth_type) {
	default:
		NDMADR_RAISE_ILLEGAL_ARGS ("auth_type");

	case NDMP9_AUTH_NONE:
		break;

	case NDMP9_AUTH_TEXT:
		break;

	case NDMP9_AUTH_MD5:
		ndmos_get_md5_challenge (sess);
		NDMOS_API_BCOPY (sess->md5_challenge,
			reply->server_attr.ndmp9_auth_attr_u.challenge, 64);
		break;
	}
	reply->server_attr.auth_type = request->auth_type;

	return 0;
      NDMS_ENDWITH
}
