G_site_c_cmp(const void *a, const void *b)


{
    int result = 0;
    double diff = 0;

    switch ((*(Site **) a)->cattype) {
    case CELL_TYPE:
	diff = (double)(*(Site **) a)->ccat - (*(Site **) b)->ccat;
	break;
    case FCELL_TYPE:
	diff = (double)(*(Site **) a)->fcat - (*(Site **) b)->fcat;
	break;
    case DCELL_TYPE:
	diff = (double)(*(Site **) a)->dcat - (*(Site **) b)->dcat;
	break;
    }
    if (diff < 0.0)
	result = -1;
    else if (diff > 0.0)
	result = 1;
    return result;
}
