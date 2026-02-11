file_pdfname2psname(char *name)
{
  char *e;

  if (!name)
    {
      return(name);
    }

  e = name+strlen(name);

  if ((e-name)-4 >= 0)
    {
      e -= 4;
      if (!strcasecmp(e,".pdf"))
	{
	  strcpy(e,".ps");
	}
    }

  return(name);
}
