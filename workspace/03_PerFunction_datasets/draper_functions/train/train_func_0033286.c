GMT_read_srfheader7 (FILE *fp, struct srf_header7 *h)
{


	if (GMT_fseek (fp, 3*sizeof(int), SEEK_SET)) return (GMT_GRDIO_SEEK_FAILED);


	if (GMT_fread ((void *)h->id2, 4*sizeof (char), (size_t)1, fp) != 1) return (GMT_GRDIO_READ_FAILED);
	if (GMT_fread ((void *)&h->len_g, 3*sizeof (int), (size_t)1, fp) != 1) return (GMT_GRDIO_READ_FAILED);
	if (GMT_fread ((void *)&h->x_min, 8*sizeof (double), (size_t)1, fp) != 1) return (GMT_GRDIO_READ_FAILED);
	if (GMT_fread ((void *)h->id3, 4*sizeof (char), (size_t)1, fp) != 1) return (GMT_GRDIO_READ_FAILED);
	if (GMT_fread ((void *)&h->len_d, sizeof (int), (size_t)1, fp) != 1) return (GMT_GRDIO_READ_FAILED);

	return (GMT_NOERROR);
}
