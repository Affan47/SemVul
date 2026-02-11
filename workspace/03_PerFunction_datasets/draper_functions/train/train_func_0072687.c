gribread_(
char* buffer,fortint* buffsize,fortint* readsize,fortint* status,fortint* unit){


fortint holdsize = *buffsize;


    *status = readprod("GRIB",buffer,&holdsize,fileRead,fileSeek,fileTell,
                       CURRENT_FILE);
    *readsize = abs(holdsize );

    if( DEBUG ) {
      printf("PBIO_GRIBREAD: fptable slot = %d. ", *unit);
      printf("Number of bytes read = %d\n", *readsize);
    }

    return;
}
