butterfly_detach(struct parport *p)
{
	struct butterfly	*pp;


	if (!butterfly || butterfly->port != p)
		return;
	pp = butterfly;
	butterfly = NULL;


	spi_bitbang_stop(&pp->bitbang);


	parport_write_data(pp->port, 0);
	msleep(10);

	parport_release(pp->pd);
	parport_unregister_device(pp->pd);

	(void) spi_master_put(pp->bitbang.master);
}
