cookies_html(FILE *fp, Cookie *cookies)
{
  int i;
  Cookie *c;

  i = 0;
  for (c = cookies; c != NULL; c = c->next) {
	fprintf(fp, "<p>");
	fprintf(fp, "Cookie %d:", i + 1);
	if (c->syntax == COOKIE_NETSCAPE)
	  fprintf(fp, "<br>Netscape format\n");
	else if (c->syntax == COOKIE_EXT_NETSCAPE)
	  fprintf(fp, "<br>Extended Netscape format\n");
	else if (c->syntax == COOKIE_RFC2109)
	  fprintf(fp, "<br>RFC 2109 format\n");
	else if (c->syntax == COOKIE_RFC2965)
	  fprintf(fp, "<br>RFC 2965 format\n");

	if (c->name != NULL)
	  fprintf(fp, "<br>name='%s'\n", c->name);
	if (c->value != NULL)
	  fprintf(fp, "<br>value='%s'\n", c->value);
	if (c->domain != NULL)
	  fprintf(fp, "<br>domain='%s'\n", c->domain);
	if (c->path != NULL)
	  fprintf(fp, "<br>path='%s'\n", c->path);
	if (c->expires != NULL)
	  fprintf(fp, "<br>expires='%s'\n", c->expires);
	if (c->max_age != NULL)
	  fprintf(fp, "<br>max-age='%s'\n", c->max_age);
	if (c->comment != NULL)
	  fprintf(fp, "<br>comment='%s'\n", c->comment);
	if (c->version != NULL)
	  fprintf(fp, "<br>version='%s'\n", c->version);
	if (c->comment_url != NULL)
	  fprintf(fp, "<br>comment_url='%s'\n", c->comment_url);
	if (c->discard != NULL)
	  fprintf(fp, "<br>discard='%s'\n", c->discard);
	if (c->port != NULL)
	  fprintf(fp, "<br>port='%s'\n", c->port);
	fprintf(fp, "<br>secure=%d\n", c->secure);
	fprintf(fp, "<br>HttpOnly=%d\n", c->httponly);
	i++;
	fflush(fp);
  }
  fprintf(fp, "<p>");
}
