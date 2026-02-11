isValidMipsElf64(Elf64_Ehdr *elfHdr)
{
	if(memcmp((char *)elfHdr->e_ident, ELFMAG, SELFMAG) == 0) {
		if(elfHdr->e_machine == EM_MIPS) {
			return 1;
		}else if(elfHdr->e_machine == EM_NONE) {
			return 1;
		}else{
#ifdef DEBUG
			printf("Not a MIPS ELF. Is %d when should be %d.\n", elfHdr->e_machine, EM_MIPS);
#endif
		}
	}else{
#ifdef DEBUG
		printf("Not an ELF.\n");
#endif
	}

	return 0;
}
