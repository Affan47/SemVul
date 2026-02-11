pswitch (int flag)
{
    sighand oldintr;
    static struct comvars {
	int connect;
	char name[MaxHostNameLen];
	struct sockaddr_storage mctl;
	struct sockaddr_storage hctl;
	FILE *in;
	FILE *out;
	int tpe;
	int curtpe;
	int cpnd;
	int sunqe;
	int runqe;
	int mcse;
	int ntflg;
	char nti[17];
	char nto[17];
	int mapflg;
	char mi[MaxPathLen];
	char mo[MaxPathLen];
    } proxstruct, tmpstruct;
    struct comvars *ip, *op;

    abrtflag = 0;
    oldintr = signal (SIGINT, psabort);
    if (flag) {
	if (proxy)
	    return;
	ip = &tmpstruct;
	op = &proxstruct;
	proxy++;
    } else {
	if (!proxy)
	    return;
	ip = &proxstruct;
	op = &tmpstruct;
	proxy = 0;
    }
    ip->connect = connected;
    connected = op->connect;
    if (hostname) {
	strlcpy (ip->name, hostname, sizeof (ip->name));
    } else
	ip->name[0] = 0;
    hostname = op->name;
    ip->hctl = hisctladdr_ss;
    hisctladdr_ss = op->hctl;
    ip->mctl = myctladdr_ss;
    myctladdr_ss = op->mctl;
    ip->in = cin;
    cin = op->in;
    ip->out = cout;
    cout = op->out;
    ip->tpe = type;
    type = op->tpe;
    ip->curtpe = curtype;
    curtype = op->curtpe;
    ip->cpnd = cpend;
    cpend = op->cpnd;
    ip->sunqe = sunique;
    sunique = op->sunqe;
    ip->runqe = runique;
    runique = op->runqe;
    ip->mcse = mcase;
    mcase = op->mcse;
    ip->ntflg = ntflag;
    ntflag = op->ntflg;
    strlcpy (ip->nti, ntin, sizeof (ip->nti));
    strlcpy (ntin, op->nti, 17);
    strlcpy (ip->nto, ntout, sizeof (ip->nto));
    strlcpy (ntout, op->nto, 17);
    ip->mapflg = mapflag;
    mapflag = op->mapflg;
    strlcpy (ip->mi, mapin, MaxPathLen);
    strlcpy (mapin, op->mi, MaxPathLen);
    strlcpy (ip->mo, mapout, MaxPathLen);
    strlcpy (mapout, op->mo, MaxPathLen);
    signal(SIGINT, oldintr);
    if (abrtflag) {
	abrtflag = 0;
	(*oldintr) (SIGINT);
    }
}
