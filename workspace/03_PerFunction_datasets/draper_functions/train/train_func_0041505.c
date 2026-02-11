do_unhide(char **av, int ac, char *arg) {
    char *dev = av[0];
    int fd, rw, i;
    struct disk_desc *z;

    z = &oldp;

    rw = !no_write;
    fd = my_open(dev, rw, 0);

    free_sectors();
    get_cylindersize(dev, fd, 1);
    get_partitions(dev, fd, z);


    if (ac == 1)
	set_unhidden(z, arg);
    else
	for (i = 1; i < ac; i++)
	    set_unhidden(z, av[i]);


    if (write_partitions(dev, fd, z))
	my_warn(_("Done\n\n"));
    else
	exit_status = 1;

    close(fd);
}
