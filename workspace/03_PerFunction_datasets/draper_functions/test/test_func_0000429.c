calibration_filename(Genesys_Device *currdev)
{
  char *tmpstr;
  char *ptr;
  char filename[80];
  Genesys_Device *dev;
  unsigned int count;
  unsigned int i;


  tmpstr=malloc(PATH_MAX);
  if(tmpstr==NULL)
    {
      return NULL;
    }


  ptr = getenv ("HOME");
  if(ptr==NULL)
    {
      ptr = getenv ("USERPROFILE");
    }
  if(ptr==NULL)
    {
      ptr = getenv ("TMPDIR");
    }
  if(ptr==NULL)
    {
      ptr = getenv ("TMP");
    }


  count=0;

  if(num_devices>1)
    {
      for (dev = first_dev; dev; dev = dev->next)
        {
          if(strcmp(dev->model->name,currdev->model->name)==0)
            {
              count++;
            }
        }
    }
  if(count>1)
    {
      snprintf(filename,sizeof(filename),"%s.cal",currdev->file_name);
      for(i=0;i<strlen(filename);i++)
        {
          if(filename[i]==':'||filename[i]==PATH_SEP)
            {
              filename[i]='_';
            }
        }
    }
  else
    {
      snprintf(filename,sizeof(filename),"%s.cal",currdev->model->name);
    }


  if (NULL == ptr)
    {
      snprintf (tmpstr, PATH_MAX, "%s", filename);
    }
  else
    {
#ifdef HAVE_MKDIR

      snprintf (tmpstr, PATH_MAX, "%s%c.sane", ptr, PATH_SEP);
      mkdir(tmpstr,0700);
#endif
      snprintf (tmpstr, PATH_MAX, "%s%c.sane%c%s", ptr, PATH_SEP, PATH_SEP, filename);
    }

  DBG (DBG_info, "%s: calibration filename >%s<\n", __FUNCTION__, tmpstr);

  return tmpstr;
}
