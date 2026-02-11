ouvre_nomenc (void)
{
	char filename[256];

	sprintf (filename, "%s%s", system_dir, INF_SYS);
	if ((fichi = fopen (filename, "rb")) == NULL)
	{
#ifdef ENGLISH
		fprintf (stderr, "Cannot find %s !!     \n", filename);
#else
		fprintf (stderr, "Erreur ouverture %s !!\n", filename);
#endif
		exit (1);
	}
}
