push(int port, Packet *p)
{
    int n = 0, nout = noutputs();
    for (int i = 0; i < nout; ++i) {
	Packet *q;
	if (i == port)
	    q = 0;
	else if (++n == nout - 1)
	    q = p;
	else
	    q = p->clone();
	if (q)
	    output(i).push(q);
    }
    if (n == 0)
	p->kill();
}
