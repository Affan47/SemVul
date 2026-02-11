u_adddir(const userinput * const u)
{
  DIR *d;
  struct dirent *f;
  char *thefile, *tempstr, *thedir;
  irlist_t dirlist = {};
  int thedirlen;

  updatecontext();

  if (!u->arg1e || !strlen(u->arg1e))
    {
      u_respond(u,"Try Specifying a Directory");
      return;
    }

  convert_to_unix_slash(u->arg1e);

  if (u->arg1e[strlen(u->arg1e)-1] == '/')
    {
      u->arg1e[strlen(u->arg1e)-1] = '\0';
    }

  thedirlen = strlen(u->arg1e);
  if (gdata.filedir)
    {
      thedirlen += strlen(gdata.filedir) + 1;
    }

  thedir = mymalloc(thedirlen+1);
  strcpy(thedir, u->arg1e);

  d = opendir(thedir);

  if (!d && (errno == ENOENT) && gdata.filedir)
    {
      snprintf(thedir, thedirlen+1, "%s/%s",
               gdata.filedir, u->arg1e);
      d = opendir(thedir);
    }

  if (!d)
    {
      u_respond(u,"Can't Access Directory: %s",strerror(errno));
      return;
    }


  while ((f = readdir(d)))
    {
      struct stat st;
      int len = strlen(f->d_name);

      tempstr = mycalloc(len + thedirlen + 2);

      snprintf(tempstr, len + thedirlen + 2,
               "%s/%s", thedir, f->d_name);

      if (stat(tempstr,&st) < 0)
        {
          u_respond(u,"cannot access %s, ignoring: %s",
                    tempstr, strerror(errno));
        }
      else if (strcmp(f->d_name,".") &&
               strcmp(f->d_name,"..") &&
               S_ISDIR(st.st_mode))
        {
          u_respond(u,"  Ignoring directory: %s", tempstr);
        }
      else if (S_ISREG(st.st_mode))
        {
          thefile = irlist_add(&dirlist, len + thedirlen + 2);
          strcpy(thefile, tempstr);
        }
      mydelete(tempstr);
    }

  closedir(d);

  irlist_sort(&dirlist, irlist_sort_cmpfunc_string, NULL);

  u_respond(u,"Adding %d files...",
            irlist_size(&dirlist));

  thefile = irlist_get_head(&dirlist);
  while (thefile)
    {
      userinput u2;
      u_respond(u,"  Adding %s:",thefile);

      u2 = *u;
      u2.arg1e = thefile;
      u_add(&u2);

      thefile = irlist_delete(&dirlist, thefile);
    }

  mydelete(thedir);
  return;
}
