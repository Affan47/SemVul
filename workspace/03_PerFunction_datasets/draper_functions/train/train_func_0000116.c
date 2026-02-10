__clear_close_on_exec(int fd, struct fdtable *fdt)
{
	if (test_bit(fd, fdt->close_on_exec))
		__clear_bit(fd, fdt->close_on_exec);
}
