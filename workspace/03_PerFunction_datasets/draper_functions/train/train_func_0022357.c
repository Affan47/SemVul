setfilename(name,ext,mode,fp)
char *name, *ext, *mode;
INT fp;
{ char yesno[10], subp[20];
  int n, quote, use_lfd;

  n = strlen(name);
  quote = ((name[0]=='"') && (name[n-1]=='"'));
  if (quote)
  { name++;
    name[n-2] = '\0';
  }

  use_lfd = (strcmp(ext,"lfd")==0) | (strcmp(ext,"fit")==0);
  if (fp)
    sprintf(filename,"%s",name);
  else
  { if (use_lfd)
      sprintf(subp,"LFData%c",DIRSEP);
    else
      sprintf(subp,"");
    if (strlen(ext)==0)
      sprintf(filename,"%s%s",subp,name);
    else
      sprintf(filename,"%s%s.%s",subp,name,ext);
  }
  if (quote) name[n-2] = '"';


  if ((mode[0]=='w') | (mode[0]=='a'))
  { if (use_lfd)
    { if (access("LFData",F_OK)==-1)
      { if (access(".",W_OK)==0)
        { printe("Creating LFData Directory...\n");
          system("mkdir LFData");
        }
      }
      if (access("LFData",W_OK)==-1)
      { ERROR(("LFData directory not writeable"));
        return(0);
      }
    }
    return(1);
  }


  if (mode[0]=='r')
  { if (access(filename,R_OK)==0) return(1);

    if ((use_lfd) && (lfhome!=NULL))
    { if (quote) name[n-2] = '\0';
      sprintf(filename,"%s/%s%s.%s",lfhome,subp,name,ext);
      if (quote) name[n-2] = '"';
      return(access(filename,R_OK)==0);
    }

    return(0);
  }
  ERROR(("setfilename: invalid mode %s",mode));
  return(0);
}
