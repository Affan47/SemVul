finishedit(void)
{
	uchar **p, **lim, **l = Gline;
	for (p=l, lim=l+Ggap;  p<lim;  ) {
		in_buffer_init(*p++, 0);
		expandline();
	}
	for (p+=Ggapsize, lim=l+Glinemax;  p<lim;  ) {
		in_buffer_init(*p++, 0);
		expandline();
	}
}
