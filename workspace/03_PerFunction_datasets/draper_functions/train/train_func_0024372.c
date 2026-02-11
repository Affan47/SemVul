fpuop_save(uae_u32 opcode)
{
	fpu_debug(("fsave_opp at %08lx\n", m68k_getpc ()));

	uae_u32 ad = 0;
	int incr = (opcode & 0x38) == 0x20 ? -1 : 1;
	int i;

	if (get_fp_ad(opcode, &ad) == 0) {
		m68k_setpc (m68k_getpc () - 2);
		op_illg (opcode);
		return;
	}

	if (CPUType == 4) {

		if (incr < 0) {
			ad -= 4;
			put_long (ad, 0x41000000);
		}
		else {
			put_long (ad, 0x41000000);
			ad += 4;
		}
	} else {

		if (incr < 0) {
			fpu_debug(("fsave_opp pre-decrement\n"));
			ad -= 4;

			put_long (ad, 0x70000000);
			for (i = 0; i < 5; i++) {
				ad -= 4;
				put_long (ad, 0x00000000);
			}
			ad -= 4;
			put_long (ad, 0x1f180000);
		}
		else {
			put_long (ad, 0x1f180000);
			ad += 4;
			for (i = 0; i < 5; i++) {
				put_long (ad, 0x00000000);
				ad += 4;
			}

			put_long (ad, 0x70000000);
			ad += 4;
		}
	}
	if ((opcode & 0x38) == 0x18) {
		m68k_areg (regs, opcode & 7) = ad;
		fpu_debug(("PROBLEM: fsave_opp post-increment\n"));
	}
	if ((opcode & 0x38) == 0x20) {
		m68k_areg (regs, opcode & 7) = ad;
		fpu_debug(("fsave_opp pre-decrement %X -> A%d\n",ad,opcode & 7));
	}
}
