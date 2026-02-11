move_fwrite_nak (char *str, FILE *fout)
{
	fprintf (fout, "NAK ");
	if (str)
		fprintf (fout, "%s", str);
	fprintf (fout, "\n");
	fflush (fout);
}
