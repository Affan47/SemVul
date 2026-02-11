init_colors(map * m)
{
    if (!red)
	red = G_malloc(columns);
    if (!grn)
	grn = G_malloc(columns);
    if (!blu)
	blu = G_malloc(columns);
    if (!set)
	set = G_malloc(columns);

    if (G3d_readColors((char *)m->name, (char *)m->mapset, &m->colors) < 0)
	G_fatal_error(_("Unable to read color file for raster map <%s@%s>"),
		      m->name, m->mapset);

    m->have_colors = 1;
}
