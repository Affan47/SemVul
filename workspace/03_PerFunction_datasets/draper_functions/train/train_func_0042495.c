realloc_sites(unsigned int n)
{

    sites = (struct vertex *)G_realloc(sites, n * sizeof(struct vertex));
    if (sites == NULL)
	G_fatal_error(_("Not enough memory."));
}
