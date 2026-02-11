patchAreaDistributionSD(int fd, char **par, area_des ad, double *result)
{
    char *mapset;
    double indice = 0;
    struct Cell_head hd;
    int ris = RLI_OK;

    mapset = G_find_cell(ad->raster, "");
    if (G_get_cellhd(ad->raster, mapset, &hd) == -1)
	return RLI_ERRORE;
    switch (ad->data_type) {
    case CELL_TYPE:

	{
	    ris = calculate(fd, ad, &indice);
	    break;
	}
    case DCELL_TYPE:

	{
	    ris = calculateD(fd, ad, &indice);
	    break;
	}
    case FCELL_TYPE:

	{
	    ris = calculateF(fd, ad, &indice);
	    break;
	}
    default:

	{
	    G_fatal_error("data type unknown");
	    return RLI_ERRORE;
	}
    }
    if (ris != RLI_OK) {
	*result = -1;
	return RLI_ERRORE;
    }
    *result = indice;
    return RLI_OK;
}
