snd_riptide_joystick_remove(struct pci_dev *pci)
{
	struct gameport *gameport = pci_get_drvdata(pci);
	if (gameport) {
		release_region(gameport->io, 8);
		gameport_unregister_port(gameport);
	}
}
