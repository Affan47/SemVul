skipext(u_char *p)
{
	while (!(*p++ & 0x80));
	return (p);
}
