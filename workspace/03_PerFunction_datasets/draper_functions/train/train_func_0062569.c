warning(const char *s, const char *t)
{
    if (client.warning)
	(*(client.warning))(client_data, fmt_error(s, t));
    else
	error(s, t);
}
