iw_get_kernel_we_version(void)
{
  char		buff[1024];
  FILE *	fh;
  char *	p;
  int		v;


  fh = fopen(PROC_NET_WIRELESS, "r");

  if(fh == NULL)
    {
      fprintf(stderr, "Cannot read " PROC_NET_WIRELESS "\n");
      return(-1);
    }


  fgets(buff, sizeof(buff), fh);

  if(strstr(buff, "| WE") == NULL)
    {


      if(strstr(buff, "| Missed") == NULL)
	v = 11;
      else
	v = 15;
      fclose(fh);
      return(v);
    }


  fgets(buff, sizeof(buff), fh);


  p = strrchr(buff, '|');
  if((p == NULL) || (sscanf(p + 1, "%d", &v) != 1))
    {
      fprintf(stderr, "Cannot parse " PROC_NET_WIRELESS "\n");
      fclose(fh);
      return(-1);
    }

  fclose(fh);
  return(v);
}
