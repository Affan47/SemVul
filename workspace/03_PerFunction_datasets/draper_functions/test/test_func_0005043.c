writedrel(buf, count)
register char *buf;
unsigned count;
{
    register char *rbuf;

    rbuf = drelbufptr;
    while (count--)
    {
	if (rbuf >= drelbuftop)
	    inputerror("data relocation buffer full while processing");
	*rbuf++ = *buf++;
    }
    drelbufptr = rbuf;
}
