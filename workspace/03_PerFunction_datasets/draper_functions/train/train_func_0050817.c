tracer(m)
struct message *m;
{
	char *fromid, *toid, fbuf[32], tbuf[32];
	unsigned char *f, *t, *iphdr;
	int ftype, ttype;

	fromid = m->from_if->id;
	ftype = m->from_if->type;
	f = (unsigned char *)&m->fip;
	if(ftype == IF_TYPE_IPUDP)
		(void)sprintf(fbuf,"(%d.%d.%d.%d:%d)",f[0],f[1],f[2],f[3],ntohs(m->fport));
	else if(ftype == IF_TYPE_IPIP)
		(void)sprintf(fbuf, "(%d.%d.%d.%d)", f[0], f[1], f[2], f[3]);
	else fbuf[0] = '\0';

	if (m->to_if) {
		toid = m->to_if->id;
		ttype = m->to_if->type;
		t = (unsigned char *)&m->tip;
	} else {
		toid = "BitBucket";
		ttype = IF_TYPE_NONE;
		t = (unsigned char *)&m->tip;
	}
	if(ttype == IF_TYPE_IPUDP)
		(void)sprintf(tbuf,"(%d.%d.%d.%d:%d)",t[0],t[1],t[2],t[3],ntohs(m->tport));
	else if(ttype == IF_TYPE_IPIP)
		(void)sprintf(tbuf, "(%d.%d.%d.%d)",t[0],t[1],t[2],t[3]);
	else tbuf[0] = '\0';

	iphdr = m->msg;

	syslog(LOG_DEBUG,"%d.%d.%d.%d->%d.%d.%d.%d len %d [%s%s->%s%s]",
		iphdr[12], iphdr[13], iphdr[14], iphdr[15],
		iphdr[16], iphdr[17], iphdr[18], iphdr[19],
		m->length, fromid, fbuf, toid, tbuf);
}
