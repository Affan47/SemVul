urldup2(old, new)
int old, new;
{
	int n;

	VOID_C _urlclose(new, "dup2");
	if ((n = urlgetopenlist(old)) >= 0)
		urlputopenlist(new, urlopenlist[n].uh,
			urlopenlist[n].path, urlopenlist[n].flags);

	return(new);
}
