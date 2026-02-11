dump_sector(int c, int h, int s)
{
	int a;

	putchar(c);
	putchar(h);
	putchar(c);
	putchar(h);
	putchar(s);
	putchar(3);
	putchar(0);
	putchar(4);

	for (a = 0;a < 1024;a++)
		putchar(0xe5);
}
