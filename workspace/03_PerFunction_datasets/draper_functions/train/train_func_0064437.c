G__write_cats(char *element, char *name, struct Categories *cats)
{
    FILE *fd;
    int i, fp_map;
    char *descr;
    DCELL val1, val2;
    char str1[100], str2[100];


    if (!(fd = G_fopen_new(element, name)))
	return -1;


    fprintf(fd, "# %ld categories\n", (long)cats->num);


    fprintf(fd, "%s\n", cats->title != NULL ? cats->title : "");


    fprintf(fd, "%s\n", cats->fmt != NULL ? cats->fmt : "");
    fprintf(fd, "%.2f %.2f %.2f %.2f\n",
	    cats->m1, cats->a1, cats->m2, cats->a2);


    if (strncmp(element, "dig", 3) == 0)
	fp_map = 0;
    else
	fp_map = G_raster_map_is_fp(name, G_mapset());

    if (!fp_map)
	G_sort_cats(cats);


    for (i = 0; i < G_quant_nof_rules(&cats->q); i++) {
	descr = G_get_ith_d_raster_cat(cats, i, &val1, &val2);
	if ((cats->fmt && cats->fmt[0])
	    || (descr && descr[0])) {
	    if (val1 == val2) {
		sprintf(str1, "%.10f", val1);
		G_trim_decimal(str1);
		fprintf(fd, "%s:%s\n", str1, descr != NULL ? descr : "");
	    }
	    else {
		sprintf(str1, "%.10f", val1);
		G_trim_decimal(str1);
		sprintf(str2, "%.10f", val2);
		G_trim_decimal(str2);
		fprintf(fd, "%s:%s:%s\n", str1, str2,
			descr != NULL ? descr : "");
	    }
	}
    }
    fclose(fd);

    return (1);
}
