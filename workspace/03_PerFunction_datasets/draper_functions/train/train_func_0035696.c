dump_Elf64_Phdr(Elf64_Phdr *prog, int store_pt_load_data)
{
	int others;
	struct pt_load_segment *pls;

	if (store_pt_load_data)
		pls = &nd->pt_load_segments[store_pt_load_data-1];
	else
		pls = NULL;

        if ((char *)prog > (nd->elf_header + nd->header_size))
		error(FATAL,
		    "Elf64_Phdr pointer: %lx  ELF header end: %lx\n\n",
			(char *)prog, nd->elf_header + nd->header_size);

	netdump_print("Elf64_Phdr:\n");
	netdump_print("                 p_type: %lx ", prog->p_type);
	switch (prog->p_type)
	{
	case PT_NULL:
		netdump_print("(PT_NULL)\n");
		break;
	case PT_LOAD:
		netdump_print("(PT_LOAD)\n");
		break;
	case PT_DYNAMIC:
		netdump_print("(PT_DYNAMIC)\n");
		break;
	case PT_INTERP:
		netdump_print("(PT_INTERP)\n");
		break;
	case PT_NOTE:
		netdump_print("(PT_NOTE)\n");
		break;
	case PT_SHLIB:
		netdump_print("(PT_SHLIB)\n");
		break;
	case PT_PHDR:
		netdump_print("(PT_PHDR)\n");
		break;
	case PT_NUM:
		netdump_print("(PT_NUM)\n");
		break;
	case PT_LOOS:
		netdump_print("(PT_LOOS)\n");
		break;
	case PT_HIOS:
		netdump_print("(PT_HIOS)\n");
		break;
	case PT_LOPROC:
		netdump_print("(PT_LOPROC)\n");
		break;
	case PT_HIPROC:
		netdump_print("(PT_HIPROC)\n");
		break;
	default:
		netdump_print("(?)\n");
	}

	netdump_print("               p_offset: %lld (%llx)\n", prog->p_offset,
		prog->p_offset);
	if (store_pt_load_data)
		pls->file_offset = prog->p_offset;
	netdump_print("                p_vaddr: %llx\n", prog->p_vaddr);
	netdump_print("                p_paddr: %llx\n", prog->p_paddr);
	if (store_pt_load_data)
		pls->phys_start = prog->p_paddr;
	netdump_print("               p_filesz: %llu (%llx)\n", prog->p_filesz,
		prog->p_filesz);
	if (store_pt_load_data) {
		pls->phys_end = pls->phys_start + prog->p_filesz;
		pls->zero_fill = (prog->p_filesz == prog->p_memsz) ?
			0 : pls->phys_start + prog->p_memsz;
	}
	netdump_print("                p_memsz: %llu (%llx)\n", prog->p_memsz,
		prog->p_memsz);
	netdump_print("                p_flags: %lx (", prog->p_flags);
	others = 0;
	if (prog->p_flags & PF_X)
		netdump_print("PF_X", others++);
	if (prog->p_flags & PF_W)
		netdump_print("%sPF_W", others++ ? "|" : "");
	if (prog->p_flags & PF_R)
		netdump_print("%sPF_R", others++ ? "|" : "");
	netdump_print(")\n");
	netdump_print("                p_align: %lld\n", prog->p_align);
}
