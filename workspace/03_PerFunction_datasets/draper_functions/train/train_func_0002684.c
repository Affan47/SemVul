check_err(int stat) {
    if (stat != NC_NOERR) {
	fprintf(stderr, "ncgen: %s\n", nc_strerror(stat));
	derror_count++;
    }
}
