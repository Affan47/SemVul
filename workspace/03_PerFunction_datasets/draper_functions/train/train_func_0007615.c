dumpsoa(struct rfc1035_reply *r, struct rfc1035_rr *rr)
{
char	name1[RFC1035_MAXNAMESIZE+1], name2[RFC1035_MAXNAMESIZE+1];
char	*p;
char	timebuf[RFC1035_MAXTIMEBUFSIZE+1];

	rfc1035_replyhostname(r, rr->rr.soa.rname_label, name1);
	rfc1035_replyhostname(r, rr->rr.soa.mname_label, name2);

	p=(char *)malloc(strlen(name1)+strlen(name2)+500);
	if (!p)	return (0);

	strcat(strcat(strcat(strcpy(p, name2), ". "), name1), ". (\n\t\t\t\t");
	sprintf(p+strlen(p), "%lu ; serial\n",
			(unsigned long)rr->rr.soa.serial);
	sprintf(p+strlen(p), "\t\t\t\t%s  ; refresh\n",
			rfc1035_fmttime( rr->rr.soa.refresh, timebuf));
	sprintf(p+strlen(p), "\t\t\t\t%s  ; retry\n",
			rfc1035_fmttime( rr->rr.soa.retry, timebuf));
	sprintf(p+strlen(p), "\t\t\t\t%s  ; expire\n",
			rfc1035_fmttime( rr->rr.soa.expire, timebuf));
	sprintf(p+strlen(p), "\t\t\t\t%s) ; minimum",
			rfc1035_fmttime( rr->rr.soa.minimum, timebuf));
	return (p);
}
