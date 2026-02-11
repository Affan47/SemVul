butterfly_attach(struct parport *p)
{
	struct pardevice	*pd;
	int			status;
	struct butterfly	*pp;
	struct spi_master	*master;
	struct device		*dev = p->physport->dev;

	if (butterfly || !dev)
		return;


	master = spi_alloc_master(dev, sizeof(*pp));
	if (!master) {
		status = -ENOMEM;
		goto done;
	}
	pp = spi_master_get_devdata(master);


	master->bus_num = 42;
	master->num_chipselect = 2;

	pp->bitbang.master = master;
	pp->bitbang.chipselect = butterfly_chipselect;
	pp->bitbang.txrx_word[SPI_MODE_0] = butterfly_txrx_word_mode0;


	pp->port = p;
	pd = parport_register_device(p, "spi_butterfly",
			NULL, NULL, NULL,
			0 , pp);
	if (!pd) {
		status = -ENOMEM;
		goto clean0;
	}
	pp->pd = pd;

	status = parport_claim(pd);
	if (status < 0)
		goto clean1;


	pr_debug("%s: powerup/reset Butterfly\n", p->name);


	parport_frob_control(pp->port, spi_cs_bit, 0);


	pp->lastbyte |= vcc_bits;
	parport_write_data(pp->port, pp->lastbyte);
	msleep(5);


	pp->lastbyte |= butterfly_nreset;
	parport_write_data(pp->port, pp->lastbyte);
	msleep(100);


	status = spi_bitbang_start(&pp->bitbang);
	if (status < 0)
		goto clean2;


	pp->info[0].max_speed_hz = 15 * 1000 * 1000;
	strcpy(pp->info[0].modalias, "mtd_dataflash");
	pp->info[0].platform_data = &flash;
	pp->info[0].chip_select = 1;
	pp->info[0].controller_data = pp;
	pp->dataflash = spi_new_device(pp->bitbang.master, &pp->info[0]);
	if (pp->dataflash)
		pr_debug("%s: dataflash at %s\n", p->name,
				dev_name(&pp->dataflash->dev));

	pr_info("%s: AVR Butterfly\n", p->name);
	butterfly = pp;
	return;

clean2:

	parport_write_data(pp->port, 0);

	parport_release(pp->pd);
clean1:
	parport_unregister_device(pd);
clean0:
	(void) spi_master_put(pp->bitbang.master);
done:
	pr_debug("%s: butterfly probe, fail %d\n", p->name, status);
}
