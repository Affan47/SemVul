proxy_init(AnInstance *self)
{
	struct proxy_private *mydata;
	char tmpbuf[80], cbuf[32];
	static char txtbuf[80];
	char *ch;

	if (self->opt == NULL)
	{
		return "Aie! no option(s): nothing to be done!";
	}

	mydata = (struct proxy_private *) malloc(sizeof(struct proxy_private));
	bzero((char *) mydata, sizeof(struct proxy_private));
	mydata->cache = NULL;
	mydata->lifetime = CACHETIME;

	tmpbuf[0] = txtbuf[0] = '\0';


	sprintf(tmpbuf, "port=%d", self->port);

	if (self->delayed)
	{
		strcat(tmpbuf, ",delayed");
		strcat(txtbuf, ", Delayed");
	}
	if (strstr(self->opt, "log"))
	{
		mydata->options |= OPT_LOG;
		strcat(tmpbuf, ",log");
		strcat(txtbuf, ", Log");
	}
	if (strstr(self->opt, "reject"))
	{
		mydata->options |= OPT_DENY;
		strcat(tmpbuf, ",reject");
		strcat(txtbuf, ", Reject");
	}
	if (strstr(self->opt, "careful"))
	{
		mydata->options |= OPT_CAREFUL;
		strcat(tmpbuf, ",careful");
		strcat(txtbuf, ", Careful");
	}

	if (mydata->options == 0)
	{
		return "Aie! unknown option(s): nothing to be done!";
	}

	if ((ch = strstr(self->opt, "cache=")))
	{
		mydata->lifetime = atoi(ch+6);
	}
	sprintf(cbuf, ",cache=%d", mydata->lifetime);
	strcat(tmpbuf, cbuf);
	sprintf(cbuf, ", Cache %d (min)", mydata->lifetime);
	strcat(txtbuf, cbuf);
	mydata->lifetime *= 60;

	self->popt = mystrdup(tmpbuf);
	self->data = mydata;
	return txtbuf+2;
}
