handle_drop(Packet *p)
{
    if (noutputs() == 1)
	p->kill();
    else
	output(1).push(p);
    _drops++;
}
