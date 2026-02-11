ide_host_remove(struct ide_host *host)
{
	ide_hwif_t *hwif;
	int i;

	ide_host_for_each_port(i, hwif, host) {
		if (hwif)
			ide_unregister(hwif);
	}

	ide_host_free(host);
}
