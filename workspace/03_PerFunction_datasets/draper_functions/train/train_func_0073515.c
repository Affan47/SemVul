do_decode_qp(struct rfc2045 *p)
{
char	*a, *b, *c, *end;
int	d;

	end=p->workbuf + p->workbuflen;
	for (a=b=p->workbuf; a < end; )
	{
		if (*a != '=')
		{
			*b++ = *a++;
			continue;
		}
		++a;
		if (!*a || a >= end || isspace((int)(unsigned char)*a))
			break;

		if ((c=strchr(xdigit, tou(*a))) == 0) continue;
		d= (c-xdigit)*16;
		++a;
		if (!*a || a >= end)
			break;
		if ((c=strchr(xdigit, tou(*a))) == 0) continue;
		d += c-xdigit;
		++a;
		*b++=d;
	}
	p->workbuflen= b-p->workbuf;
	d=(*p->udecode_func)(p->workbuf, p->workbuflen, p->misc_decode_ptr);
	p->workbuflen=0;
	return (d);
}
