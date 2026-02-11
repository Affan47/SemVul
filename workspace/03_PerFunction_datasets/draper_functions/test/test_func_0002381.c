decode_qp(struct rfc2045 *p, const char *s, size_t l)
{
size_t	start,i;
int	rc;

	if (!s)
		return (do_decode_qp(p));

	for (start=0; start<l; )
	{
		for (i=start; i<l; i++)
		{
			if (s[i] != '\n') continue;
			rfc2045_add_workbuf(p, s+start, i-start);
			rfc2045_add_workbufch(p, '\n');
			if ((rc=do_decode_qp(p)) != 0)	return (rc);
			start= ++i;
			break;
		}
		rfc2045_add_workbuf(p, s+start, i-start);
		if (p->workbuflen > 1024)
		{
		char	buf[10];
		int	i;

			for (i=p->workbuflen - 5; i<p->workbuflen; i++)
				if (p->workbuf[i] == '=')	break;
			if (i < p->workbuflen)
			{
			int j=p->workbuflen-i;

				memcpy(buf, p->workbuf+i, j);
				buf[j]=0;
				p->workbuflen=i;
			}
			else	buf[0]=0;
			if ((rc=do_decode_qp(p)) != 0)	return (rc);
			rfc2045_add_workbuf(p, buf, strlen(buf));
		}
		start=i;
	}
	return (0);
}
