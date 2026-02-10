exec_internal(request_rec *r, const char *extpath)
{

  ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
			   "mod_auth_dacs: Unsupported authentication method: \"internal\"");
  return(HTTP_INTERNAL_SERVER_ERROR);
}
