add_read_stdin(struct add_info *p)
{
	int n=read(0, p->buffer, sizeof(p->buffer));

	p->bufptr=p->buffer;
	if (n < 0)
		return (n);
	p->bufleft=n;
	return (0);
}
