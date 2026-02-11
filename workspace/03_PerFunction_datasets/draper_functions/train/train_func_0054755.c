mantis_ca_slot_shutdown(struct dvb_ca_en50221 *en50221, int slot)
{
	struct mantis_ca *ca = en50221->data;
	struct mantis_pci *mantis = ca->ca_priv;

	dprintk(MANTIS_DEBUG, 1, "Slot(%d): Slot shutdown", slot);

	return 0;
}
