count_events_from_csv_files(int max_files, const char *path, int *result)
{
  int evt_cnt=0, k;

  char scratchpad[2048],
       csvfilepath[MAX_PATH_LENGTH],
       linebuf[1024],
       *ptr;

  FILE *csvfile;


  *result = 0;

  for(k=0; k<max_files; k++)
  {
    get_directory_from_path(csvfilepath, path, MAX_PATH_LENGTH);

    strcat(csvfilepath, "/");
    strcat(csvfilepath, evtfilename[k]);

    csvfile = fopeno(csvfilepath, "rb");
    if(csvfile == NULL)
    {
      sprintf(scratchpad, "Error, can not open csv file:\n%s\n", evtfilename[k]);
      textEdit1->append(QString::fromLocal8Bit(scratchpad));
      return(1);
    }

    while(1)
    {
      ptr = fgets(linebuf, 1024, csvfile);

      if(ptr == NULL)  break;

      evt_cnt++;
    }

    fclose(csvfile);
  }

  *result = evt_cnt;

  return(0);
}
