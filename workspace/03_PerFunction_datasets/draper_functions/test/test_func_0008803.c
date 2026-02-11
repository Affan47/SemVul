na_ptr (void)
{
    double *px = malloc(sizeof *px);

    if (px != NULL) {
	*px = NADBL;
    }

    return px;
}
