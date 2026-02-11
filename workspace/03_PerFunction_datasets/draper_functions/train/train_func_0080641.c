G_sites_close(struct Map_info *Map)
{
    int i, j;

    if (Map->mode == GV_MODE_WRITE || Map->mode == GV_MODE_RW)
	Vect_build(Map);

    Vect_close(Map);

    for (i = 0; i < Map->n_site_att; i++) {
	free(Map->site_att[i].dbl);

	for (j = 0; j < Map->n_site_str; j++)
	    free(Map->site_att[i].str[j]);

	free(Map->site_att[i].str);
    }
    free(Map->site_att);

    G_free(Map);
}
