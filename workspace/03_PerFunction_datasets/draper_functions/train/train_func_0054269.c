prb_getline(int fd, struct protoreadbuf *prb)
{
	int i=0;
	char c;

	while ((c=PRB_GETCH(fd, prb)) != '\n')
	{
		if ( i < sizeof (prb->line)-1)
			prb->line[i++]=c;
	}
	prb->line[i]=0;
	return (prb->line);
}
