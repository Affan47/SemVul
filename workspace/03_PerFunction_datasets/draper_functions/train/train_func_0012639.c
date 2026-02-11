get_netdump_regs(struct bt_info *bt, ulong *eip, ulong *esp)
{
	int e_machine;

        if (nd->elf32)
        	e_machine = nd->elf32->e_machine;
        else if (nd->elf64)
       		e_machine = nd->elf64->e_machine;
        else
        	e_machine = EM_NONE;

        switch (e_machine)
	{
	case EM_386:
		return get_netdump_regs_x86(bt, eip, esp);
		break;

	case EM_IA_64:


		machdep->get_stack_frame(bt, eip, esp);
		break;

	case EM_PPC:
		return get_netdump_regs_ppc(bt, eip, esp);
		break;

	case EM_PPC64:
		return get_netdump_regs_ppc64(bt, eip, esp);
		break;

	case EM_X86_64:
		return get_netdump_regs_x86_64(bt, eip, esp);
		break;

	case EM_S390:
		machdep->get_stack_frame(bt, eip, esp);
		break;

	case EM_ARM:
		return get_netdump_regs_arm(bt, eip, esp);
		break;

	case EM_AARCH64:
		return get_netdump_regs_arm64(bt, eip, esp);
		break;

	default:
		error(FATAL,
		   "support for ELF machine type %d not available\n",
			e_machine);
	}
}
