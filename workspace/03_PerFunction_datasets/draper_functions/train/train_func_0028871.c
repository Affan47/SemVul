uncancelevent(struct PCPnet *pn, const char *id,
			 int flags, struct PCP_uncancel *ui)
{
	char *buf;

	pn->haserrmsg=0;
	if (ui)
		ui->errcode=0;

	if (strchr(id, '\r') || strchr(id, '\n'))
	{
		errno=EINVAL;
		return (-1);
	}
	if (docmd(pn, "RSET\n", 0))
		return (-1);
	pn->haserrmsg=1;

	switch (checkstatus(pn, NULL) / 100) {
	case 1:
	case 2:
	case 3:
		break;
	default:
		return (-1);
	}

	pn->haserrmsg=0;
	if (docmd(pn, flags & PCP_OK_CONFLICT
		  ? "CONFLICT ON\n":"CONFLICT OFF\n", 0))
	{
		return (-1);
	}
	if (docmd(pn, flags & PCP_OK_PROXY_ERRORS
		  ? "FORCE ON\n":"FORCE OFF\n", 0))
	{
		return (-1);
	}

	pn->haserrmsg=1;

	switch (checkstatus(pn, NULL) / 100) {
	case 1:
	case 2:
	case 3:
		break;
	default:
		return (-1);
	}

	buf=malloc(strlen(id)+20);
	if (!buf)
		return (-1);

	strcat(strcat(strcpy(buf, "UNCANCEL "), id), "\n");
	if (dowrite(pn, buf, 0))
	{
		free(buf);
		return (-1);
	}

	return (docommitresponse(pn, ui ? ui->uncancel_conflict_callback:NULL,
				 ui ? ui->uncancel_conflict_callback_ptr:NULL,
				 ui ? &ui->errcode:NULL));
}
