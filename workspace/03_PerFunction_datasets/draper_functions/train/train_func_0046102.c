ide_host_register(struct ide_host *host, const struct ide_port_info *d,
		      struct ide_hw **hws)
{
	ide_hwif_t *hwif, *mate = NULL;
	int i, j = 0;

	ide_host_for_each_port(i, hwif, host) {
		if (hwif == NULL) {
			mate = NULL;
			continue;
		}

		ide_init_port_hw(hwif, hws[i]);
		ide_port_apply_params(hwif);

		if ((i & 1) && mate) {
			hwif->mate = mate;
			mate->mate = hwif;
		}

		mate = (i & 1) ? NULL : hwif;

		ide_init_port(hwif, i & 1, d);
		ide_port_cable_detect(hwif);

		hwif->port_flags |= IDE_PFLAG_PROBING;

		ide_port_init_devices(hwif);
	}

	ide_host_for_each_port(i, hwif, host) {
		if (hwif == NULL)
			continue;

		if (ide_probe_port(hwif) == 0)
			hwif->present = 1;

		hwif->port_flags &= ~IDE_PFLAG_PROBING;

		if ((hwif->host_flags & IDE_HFLAG_4DRIVES) == 0 ||
		    hwif->mate == NULL || hwif->mate->present == 0) {
			if (ide_register_port(hwif)) {
				ide_disable_port(hwif);
				continue;
			}
		}

		if (hwif->present)
			ide_port_tune_devices(hwif);
	}

	ide_host_enable_irqs(host);

	ide_host_for_each_port(i, hwif, host) {
		if (hwif == NULL)
			continue;

		if (hwif_init(hwif) == 0) {
			printk(KERN_INFO "%s: failed to initialize IDE "
					 "interface\n", hwif->name);
			device_unregister(&hwif->gendev);
			ide_disable_port(hwif);
			continue;
		}

		if (hwif->present)
			if (ide_port_setup_devices(hwif) == 0) {
				hwif->present = 0;
				continue;
			}

		j++;

		ide_acpi_init_port(hwif);

		if (hwif->present)
			ide_acpi_port_init_devices(hwif);
	}

	ide_host_for_each_port(i, hwif, host) {
		if (hwif == NULL)
			continue;

		ide_sysfs_register_port(hwif);
		ide_proc_register_port(hwif);

		if (hwif->present) {
			ide_proc_port_register_devices(hwif);
			hwif_register_devices(hwif);
		}
	}

	return j ? 0 : -1;
}
