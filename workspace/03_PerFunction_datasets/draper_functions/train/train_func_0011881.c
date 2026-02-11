miseaplat_instph(char *insname, char cheminom)
{

	if (mode_debug)
		printf("mise a plat de l'instance %s et cheminon %d\n", insname, (int)cheminom);

	GENLIB_FLATTEN_PHFIG(insname, cheminom);
}
