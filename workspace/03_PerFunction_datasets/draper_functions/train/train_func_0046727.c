deletelines(unsigned long n, unsigned long nlines)
{
	unsigned long l = n + nlines;
	if (Glinemax-Ggapsize < l  ||  l < n)
		fatal_error("edit script tried to delete beyond eof");
	if (l < Ggap)
		memmove(Gline+l+Ggapsize, Gline+l, (Ggap-l) * sizeof(uchar *));
	else if (Ggap < n)
		memmove(Gline+Ggap, Gline+Ggap+Ggapsize, (n-Ggap) * sizeof(uchar *));
	Ggap = n;
	Ggapsize += nlines;
}
