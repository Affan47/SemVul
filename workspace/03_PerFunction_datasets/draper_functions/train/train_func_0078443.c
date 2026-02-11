elf32_dyn_dump (Elf32_Dyn *dyn, const char *strtab)
{
	printf ("    Dynamic linking tag:            %u\n", dyn->d_tag);
	printf ("    Dynamic linking val/addr:       %u\n", dyn->d_un.d_val);
	if (strtab && dyn->d_tag == DT_NEEDED)
		printf ("    Dynamically Linked Library:     %s\n", strtab + dyn->d_un.d_val);
	printf ("\n");
}
