main(int argc, char *argv[])
{
    void *data;
    size_t data_len;
    addr_t where;

    openconsole(&dev_null_r, &dev_stdcon_w);

    if (argc < 3) {
	error("Usage: pmload.c32 bin_file address arguments...\n");
	return 1;
    }

    where = strtoul(argv[2], NULL, 0);

    if (loadfile(argv[1], &data, &data_len)) {
	error("Unable to load file\n");
	return 1;
    }

    boot_raw(data, data_len, where, &argv[1]);
    error("Failed to boot, probably insufficient memory\n");
    return 1;
}
