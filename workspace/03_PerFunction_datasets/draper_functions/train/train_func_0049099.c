GMT_native_skip_grd_header (FILE *fp, struct GRD_HEADER *header)
{
	GMT_LONG err = GMT_NOERROR;


	if (GMT_fseek (fp, (long)(3*sizeof (int) + sizeof (struct GRD_HEADER) - ((long)&header->x_min - (long)&header->nx)), SEEK_SET))
                err = GMT_GRDIO_SEEK_FAILED;
	return (err);
}
