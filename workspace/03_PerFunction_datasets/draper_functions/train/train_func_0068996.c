Gem_addownpath(const char*filename) {
    char buf[MAXPDSTRING];
    char*bufptr=NULL;
    int fd=-1;

    int flags=O_RDONLY;
# ifdef _WIN32
    flags |= _O_BINARY;
# endif


    if ((fd=canvas_open(NULL, filename, "", buf, &bufptr, MAXPDSTRING, 1))>=0){
      close(fd);
      return;
    }

    char*mypath=0;
    t_gemclass *c = (t_gemclass*)class_new(gensym("Gem"), 0, 0, 0, 0, A_NULL);
    mypath=c->c_externdir->s_name;


    snprintf(buf, MAXPDSTRING-1, "%s/%s", mypath, filename);
    buf[MAXPDSTRING-1]=0;
    if ((fd=open(buf, flags))>=0){
      close(fd);
    } else {

      return;
    }

    verbose(1, "eventually adding Gem path '%s' to search-paths", mypath);
# ifndef _MSC_VER

    sys_searchpath = namelist_append(sys_searchpath, mypath, 0);
# endif
  }
