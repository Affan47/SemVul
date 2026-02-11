gn_vm_initialise(const char *iname, const char *bindir, int debug_mode, int GSMInit)
{
	static struct gn_statemachine State;
	sm = &State;
	queue.n = 0;
	queue.head = 0;
	queue.tail = 0;

	CommandMode = true;

	if (debug_mode == true) {
		UseSTDIO = true;
	} else {
		UseSTDIO = false;
	}

	if (GSMInit) {
		dprintf("Initialising GSM\n");
		if (gn_cfg_phone_load(iname, sm) != GN_ERR_NONE) return false;
		if ((VM_GSMInitialise(sm) != GN_ERR_NONE)) {
			fprintf (stderr, _("gn_vm_initialise - VM_GSMInitialise failed!\n"));
			return (false);
		}
	}
	GSMInit = false;

	if (VM_PtySetup(bindir) < 0) {
		fprintf (stderr, _("gn_vm_initialise - VM_PtySetup failed!\n"));
		return (false);
	}

	if (gn_atem_initialise(PtyRDFD, PtyWRFD, sm) != true) {
		fprintf (stderr, _("gn_vm_initialise - gn_atem_initialise failed!\n"));
		return (false);
	}

	if (dp_Initialise(PtyRDFD, PtyWRFD) != true) {
		fprintf (stderr, _("gn_vm_initialise - dp_Initialise failed!\n"));
		return (false);
	}

	return (true);
}
