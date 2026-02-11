G_read_fp_range(const char *name, const char *mapset,
		    struct FPRange *drange)
{
    struct Range range;
    int fd;
    char buf[200], xdr_buf[100];
    DCELL dcell1, dcell2;
    XDR xdr_str;

    G_init_fp_range(drange);

    if (G_raster_map_type(name, mapset) == CELL_TYPE) {


	if (G_read_range(name, mapset, &range) >= 0) {

	    if (range.first_time)
		return 2;

	    G_update_fp_range((DCELL) range.min, drange);
	    G_update_fp_range((DCELL) range.max, drange);
	    return 1;
	}
	return -1;
    }

    fd = -1;

    if (G_find_file2_misc("cell_misc", "f_range", name, mapset)) {
	fd = G_open_old_misc("cell_misc", "f_range", name, mapset);
	if (fd < 0)
	    goto error;

	if (read(fd, xdr_buf, 2 * XDR_DOUBLE_NBYTES) != 2 * XDR_DOUBLE_NBYTES)
	    return 2;

	xdrmem_create(&xdr_str, xdr_buf, (u_int) XDR_DOUBLE_NBYTES * 2,
		      XDR_DECODE);


	if (!xdr_double(&xdr_str, &dcell1) || !xdr_double(&xdr_str, &dcell2))
	    goto error;

	G_update_fp_range(dcell1, drange);
	G_update_fp_range(dcell2, drange);
	close(fd);
	return 1;
    }

  error:
    if (fd > 0)
	close(fd);
    sprintf(buf, _("can't read f_range file for [%s in %s]"), name, mapset);
    G_warning(buf);
    return -1;
}
