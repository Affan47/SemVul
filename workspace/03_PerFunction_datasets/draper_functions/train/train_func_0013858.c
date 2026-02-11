ab_nameaddr_show(const char *name, const char *addr)
{
	if (name)
	{
		printf("\"");
		ab_show_utf8(name);
		printf("\"&nbsp;");
	}
	printf("&lt;");

	if (addr)
		ab_show_utf8(addr);

	printf("&gt;");
}
