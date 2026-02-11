set_cookie_output_syntax(Cookie_syntax syntax)
{

  if (syntax == COOKIE_NETSCAPE || syntax == COOKIE_EXT_NETSCAPE) {
	cookie_output_syntax = syntax;
	return(0);
  }

  log_msg((LOG_ERROR_LEVEL,
		   "Attempt to select unsupported cookie output syntax"));
  return(-1);
}
