read_row(int fd, void *buf, int row, int dummy)
{
    if (G_get_raster_row(fd, (DCELL *) buf, row, read_row_type) < 0)
	G_fatal_error(_("Unable to read raster map row %d"), row);

    return 0;
}
