count_reloc(Elf32_Rel *rel, Elf32_Sym *sym)
{
	if (ELF32_R_TYPE(rel->r_info) == R_386_16)
		reloc16_count++;
	else
		reloc_count++;
}
