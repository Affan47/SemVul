get_segy_reelhd (fileptr, reelhead)
	FILE *fileptr;
	char *reelhead;
{
	size_t igot;


        if ((igot = fread (reelhead, (size_t)3200, (size_t)1, fileptr)) != 1) {
		fprintf(stderr,"Error reading SEGY reel header \n");
		exit(1);
		}
	return (TRUE);
}
