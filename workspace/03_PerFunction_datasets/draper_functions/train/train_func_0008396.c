cst_track_save_est(cst_track *t, const char *filename)
{
    cst_file fd;
    int i,j;

    if ((fd = cst_fopen(filename,CST_OPEN_WRITE|CST_OPEN_BINARY)) == NULL)
    {
	cst_errmsg("cst_track_save_est: can't open file \"%s\"\n",
		   filename);
	return -1;
    }

    cst_fprintf(fd,"EST_File Track\n");
    cst_fprintf(fd,"DataType ascii\n");
    cst_fprintf(fd,"NumFrames %d\n",t->num_frames);
    cst_fprintf(fd,"NumChannels %d\n",t->num_channels);
    cst_fprintf(fd,"BreaksPresent true\n");
    cst_fprintf(fd,"EST_Header_End\n");

    for (i=0; i < t->num_frames; i++)
    {
	cst_fprintf(fd,"%f\t1 \t",t->times[i]);
	for (j=0; j < t->num_channels; j++)
	    cst_fprintf(fd,"%f ",t->frames[i][j]);
	cst_fprintf(fd,"\n");
    }

    cst_fclose(fd);

    return 0;
}
