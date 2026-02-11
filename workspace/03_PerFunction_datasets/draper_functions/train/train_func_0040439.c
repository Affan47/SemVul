is_selected_cookie_name(char *cookie_name)
{
  char *cn;

  cn = make_selected_cookie_name();
  if (streq(cookie_name, cn))
	return(1);

  return(0);
}
