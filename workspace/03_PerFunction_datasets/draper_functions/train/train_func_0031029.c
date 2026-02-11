run() {
	if (do_skip || do_skip_value || do_breakpoints) {
		bool success = false;

		if (do_skip && (m68k_getpc() == skipaddr)) {
			do_skip = false;
			success = true;
		}

		if (do_skip_value) {
			switch (value_test) {
				case EQUAL_value_test_8:
					if (ReadAtariInt8(value_addr) == value) {
						do_skip_value = false;
						success = true;
					}
					break;
				case EQUAL_value_test_16:
					if (ReadAtariInt16(value_addr) == value){
						do_skip_value = false;
						success = true;
					}
					break;
				case EQUAL_value_test_32:
					if (ReadAtariInt32(value_addr) == value){
						do_skip_value = false;
						success = true;
					}
					break;
				case CHANGE_value_test_8:
					if (ReadAtariInt8(value_addr) != value) {
						do_skip_value = false;
						success = true;
					}
					break;
				case CHANGE_value_test_16:
					if (ReadAtariInt16(value_addr) != value){
						do_skip_value = false;
						success = true;
					}
					break;
				case CHANGE_value_test_32:
					if (ReadAtariInt32(value_addr) != value){
						do_skip_value = false;
						success = true;
					}
					break;
			}
		}

		if (do_breakpoints) {
			unsigned int i;
			for (i = 0; i < max_breakpoints; i++)
				if ((breakpoint[i]) && (breakpoint_address[i] == m68k_getpc()))
					break;
			if (i < max_breakpoints)
				success = true;
		}

		if (!success) {
			SPCFLAGS_SET( SPCFLAG_BRK );
			return;
		}
	}

	irqindebug = false;

	bool wasGrabbed = grabMouse(false);

	uaecptr nextpc, nxdis, nxmem;
	newm68k_disasm(stderr, m68k_getpc(), &nextpc, 0);
	nxdis = nextpc;
	nxmem = 0;

	for (;;) {
		switch(tp) {
			default:
			case 0:
				if (canon(stderr, wasGrabbed, nextpc, nxdis, nxmem) == 0) return;
				break;
			case 1:
				if (icanon(stderr, wasGrabbed, nextpc, nxdis, nxmem) == 0) return;
				break;
			case 2:
				if (dm(stderr, wasGrabbed, nextpc, nxdis, nxmem) == 0) return;
				break;
		}
	}
}
