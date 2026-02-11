initUnasm()
{
	bool pe64 = false;
	if (pe_shared->opt_magic == COFF_OPTMAGIC_PE64) {
		pe64 = true;
	}
	DPRINTF("pe_analy: ");
	if (pe_shared->il) {
		analy_disasm = new AnalyILDisassembler();
		((AnalyILDisassembler *)analy_disasm)->init(this, string_func, token_func, pe_shared);
	} else {
		switch (pe_shared->coffheader.machine) {
		case COFF_MACHINE_I386:
		case COFF_MACHINE_I486:
		case COFF_MACHINE_I586:
			if (pe64) {
				errorbox("x86 cant be used in PE64 format.");
			} else {
				DPRINTF("initing analy_x86_disassembler\n");
				analy_disasm = new AnalyX86Disassembler();
				((AnalyX86Disassembler *)analy_disasm)->init(this, 0);
			}
			break;
		case COFF_MACHINE_AMD64:
			if (!pe64) {
				errorbox("x86_64 cant be used in PE32 format.");
			} else {
				analy_disasm = new AnalyX86Disassembler();
				((AnalyX86Disassembler *)analy_disasm)->init(this, ANALYX86DISASSEMBLER_FLAGS_AMD64);
			}
			break;
		case COFF_MACHINE_R3000:
			DPRINTF("no apropriate disassembler for MIPS\n");
			warnbox("No disassembler for MIPS!");
			break;
		case COFF_MACHINE_R4000:
			DPRINTF("no apropriate disassembler for MIPS\n");
			warnbox("No disassembler for MIPS!");
			break;
		case COFF_MACHINE_R10000:
			DPRINTF("no apropriate disassembler for MIPS\n");
			warnbox("No disassembler for MIPS!");
			break;
		case COFF_MACHINE_ALPHA:
			DPRINTF("initing alpha_axp_disassembler\n");
			analy_disasm = new AnalyAlphaDisassembler();
			((AnalyAlphaDisassembler *)analy_disasm)->init(this);
			break;
		case COFF_MACHINE_POWERPC_LE:
			DPRINTF("no apropriate disassembler for POWER PC\n");
			warnbox("No disassembler for little endian POWER PC!");
			break;
		case COFF_MACHINE_POWERPC_BE:
		case COFF_MACHINE_POWERPC64_BE:
			analy_disasm = new AnalyPPCDisassembler();
			((AnalyPPCDisassembler*)analy_disasm)->init(this, pe64 ? ANALY_PPC_64 : ANALY_PPC_32);
			break;
		case COFF_MACHINE_IA64:
			if (!pe64) {
				errorbox("Intel IA64 cant be used in PE32 format.");
			} else {
				analy_disasm = new AnalyIA64Disassembler();
				((AnalyIA64Disassembler*)analy_disasm)->init(this);
			}
			break;
		case COFF_MACHINE_ARM:
		case COFF_MACHINE_THUMB:
			DPRINTF("initing arm_disassembler\n");
			analy_disasm = new AnalyArmDisassembler();
			((AnalyArmDisassembler *)analy_disasm)->init(this);
                        break;
		case COFF_MACHINE_UNKNOWN:
		default:
			DPRINTF("no apropriate disassembler for machine %04x\n", pe_shared->coffheader.machine);
			warnbox("No disassembler for unknown machine type %04x!", pe_shared->coffheader.machine);
		}
	}
}
