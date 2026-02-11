is_dacs_admin(Credentials *credentials)
{
  Credentials *cr;

  for (cr = credentials; cr != NULL; cr = cr->next) {
	if (cr->auth_style == AUTH_STYLE_ADMIN)
	  return(1);

	if (is_dacs_admin_identity(cr->federation, cr->home_jurisdiction,
							   cr->username) == 1) {
	  log_msg((LOG_TRACE_LEVEL, "Matched admin identity: %s",
			   auth_identity_from_credentials(cr)));
	  return(1);
	}
	log_msg((LOG_TRACE_LEVEL, "No admin identity match: %s",
			 auth_identity_from_credentials(cr)));
  }

  return(0);
}
