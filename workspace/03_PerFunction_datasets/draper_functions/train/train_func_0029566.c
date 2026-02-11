PackDAWG (infp, outfp)
    FILE *infp;
    FILE *outfp;
{
    char buffer[STRINGSIZE];

    ResetDAWG ();

    fputs (dawgmagic, outfp);

    while (fgets (buffer, STRINGSIZE, infp))
    {
	PutDAWG (outfp, buffer);
    }

    return (0);
}
