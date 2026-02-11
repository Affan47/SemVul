fftsad(fitsfile   *mfptr,
	   HDUtracker *HDU,
	   int        *newPosition,
	   char       *newFileName)


{
  int i;
  int hdunum;
  int status = 0;

  char filename1[FLEN_FILENAME];
  char filename2[FLEN_FILENAME];

  do
    {


      fits_get_hdu_num(mfptr,&hdunum);


      status = fits_file_name(mfptr,filename1,&status);


      status = ffrtnm(filename1,filename2,&status);


      for(i = 0;
       i < HDU->nHDU &&  !(HDU->position[i] == hdunum
			   && strcmp(HDU->filename[i],filename2) == 0);
	  ++i);

      if(i != HDU->nHDU)
	{
	  status = HDU_ALREADY_TRACKED;
	  if(newPosition != NULL) *newPosition = HDU->newPosition[i];
	  if(newFileName != NULL) strcpy(newFileName,HDU->newFilename[i]);
	  continue;
	}

      if(HDU->nHDU == MAX_HDU_TRACKER)
	{
	  status = TOO_MANY_HDUS_TRACKED;
	  continue;
	}

      HDU->filename[i] = (char*) malloc(FLEN_FILENAME * sizeof(char));

      if(HDU->filename[i] == NULL)
	{
	  status = MEMORY_ALLOCATION;
	  continue;
	}

      HDU->newFilename[i] = (char*) malloc(FLEN_FILENAME * sizeof(char));

      if(HDU->newFilename[i] == NULL)
	{
	  status = MEMORY_ALLOCATION;
	  free(HDU->filename[i]);
	  continue;
	}

      HDU->position[i]    = hdunum;
      HDU->newPosition[i] = hdunum;

      strcpy(HDU->filename[i],filename2);
      strcpy(HDU->newFilename[i],filename2);

       ++(HDU->nHDU);

    }while(0);

  return(status);
}
