file_is_compressed(char *filename)


{
    FILE *diskfile;
    unsigned char buffer[2];
    char tmpfilename[FLEN_FILENAME];


    if (file_openfile(filename, 0, &diskfile))
    {
      if (strlen(filename) > FLEN_FILENAME - 1)
          return(0);

      strcpy(tmpfilename,filename);
      strcat(filename,".gz");
      if (file_openfile(filename, 0, &diskfile))
      {
        strcpy(filename, tmpfilename);
        strcat(filename,".Z");
        if (file_openfile(filename, 0, &diskfile))
        {
          strcpy(filename, tmpfilename);
          strcat(filename,".z");
          if (file_openfile(filename, 0, &diskfile))
          {
            strcpy(filename, tmpfilename);
            strcat(filename,".zip");
            if (file_openfile(filename, 0, &diskfile))
            {
              strcpy(filename, tmpfilename);
              strcat(filename,"-z");
              if (file_openfile(filename, 0, &diskfile))
              {
                strcpy(filename, tmpfilename);
                strcat(filename,"-gz");
                if (file_openfile(filename, 0, &diskfile))
                {
                  strcpy(filename,tmpfilename);
                  return(0);
                }
              }
            }
          }
        }
      }
    }

    if (fread(buffer, 1, 2, diskfile) != 2)
    {
        fclose(diskfile);
        return(0);
    }

    fclose(diskfile);


    if ( (memcmp(buffer, "\037\213", 2) == 0) ||
         (memcmp(buffer, "\120\113", 2) == 0) ||
         (memcmp(buffer, "\037\036", 2) == 0) ||
         (memcmp(buffer, "\037\235", 2) == 0) ||
         (memcmp(buffer, "\037\240", 2) == 0) )
        {
            return(1);
        }
    else
        {
            return(0);
        }
}
