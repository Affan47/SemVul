print_io_api(long io_types)
{
    if (io_types & SIO_POSIX)
	HDfprintf(output, "posix ");
    if (io_types & SIO_HDF5)
	HDfprintf(output, "hdf5 ");
    HDfprintf(output, "\n");
}
