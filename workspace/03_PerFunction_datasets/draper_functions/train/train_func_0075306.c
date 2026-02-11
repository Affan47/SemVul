plD_eop_pbm(PLStream *pls)
{
    FILE *fp = pls->OutFile;
    int iw;

    if (fp != NULL) {
	fprintf(fp, "%s\n", "P6");
	fprintf(fp, "%d %d\n", pls->xlength, pls->ylength);
	fprintf(fp, "%d\n", MAX_INTENSITY);


	iw = fwrite( cmap, 1, pls->xlength * pls->ylength * 3, fp );

	fclose(fp);
    }
    free(cmap);
    cmap = 0;
}
