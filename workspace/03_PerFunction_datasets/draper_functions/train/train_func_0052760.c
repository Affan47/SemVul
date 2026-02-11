synth_probe(struct spk_synth *synth)
{
	unsigned int port_val = 0;
	int i = 0;

	pr_info("Probing for %s.\n", synth->long_name);
	if (port_forced) {
		synth_port = port_forced;
		pr_info("probe forced to %x by kernel command line\n",
				synth_port);
		if (synth_request_region(synth_port-1, SYNTH_IO_EXTENT)) {
			pr_warn("sorry, port already reserved\n");
			return -EBUSY;
		}
		port_val = inb(synth_port);
	} else {
		for (i = 0; synth_portlist[i]; i++) {
			if (synth_request_region(synth_portlist[i],
						SYNTH_IO_EXTENT)) {
				pr_warn
				    ("request_region: failed with 0x%x, %d\n",
				     synth_portlist[i], SYNTH_IO_EXTENT);
				continue;
			}
			port_val = inb(synth_portlist[i]);
			if (port_val == 0x80) {
				synth_port = synth_portlist[i];
				break;
			}
		}
	}
	if (port_val != 0x80) {
		pr_info("%s: not found\n", synth->long_name);
		synth_release_region(synth_port, SYNTH_IO_EXTENT);
		synth_port = 0;
		return -ENODEV;
	}
	pr_info("%s: %03x-%03x, driver version %s,\n", synth->long_name,
		synth_port, synth_port+SYNTH_IO_EXTENT-1,
		synth->version);
	synth->alive = 1;
	return 0;
}
