snd_als4000_create_gameport(struct snd_card_als4000 *acard, int dev)
{
	struct gameport *gp;
	struct resource *r;
	int io_port;

	if (joystick_port[dev] == 0)
		return -ENODEV;

	if (joystick_port[dev] == 1) {
		for (io_port = 0x200; io_port <= 0x218; io_port += 8) {
			r = request_region(io_port, 8, "ALS4000 gameport");
			if (r)
				break;
		}
	} else {
		io_port = joystick_port[dev];
		r = request_region(io_port, 8, "ALS4000 gameport");
	}

	if (!r) {
		dev_warn(&acard->pci->dev, "cannot reserve joystick ports\n");
		return -EBUSY;
	}

	acard->gameport = gp = gameport_allocate_port();
	if (!gp) {
		dev_err(&acard->pci->dev, "cannot allocate memory for gameport\n");
		release_and_free_resource(r);
		return -ENOMEM;
	}

	gameport_set_name(gp, "ALS4000 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(acard->pci));
	gameport_set_dev_parent(gp, &acard->pci->dev);
	gp->io = io_port;
	gameport_set_port_data(gp, r);


	snd_als4000_set_addr(acard->iobase, 0, 0, 0, 1);

	gameport_register_port(acard->gameport);

	return 0;
}
