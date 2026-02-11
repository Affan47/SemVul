print_datasize (int datasize)
{
	if (Debug > 2) {
	char buf [32];
	sprintf (buf, "Datasize: %d bits ", datasize);
	strcat (Debugbuf, buf);
	}
}
