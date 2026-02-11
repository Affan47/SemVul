kwsysProcessKill(pid_t process_id)
{
#if defined(__linux__) || defined(__CYGWIN__)
  DIR* procdir;
#endif


  kill(process_id, SIGSTOP);


#if defined(__linux__) || defined(__CYGWIN__)

  if((procdir = opendir("/proc")) != NULL)
    {
#if defined(MAXPATHLEN)
    char fname[MAXPATHLEN];
#elif defined(PATH_MAX)
    char fname[PATH_MAX];
#else
    char fname[4096];
#endif
    char buffer[KWSYSPE_PIPE_BUFFER_SIZE+1];
    struct dirent* d;


    for(d = readdir(procdir); d; d = readdir(procdir))
      {
      int pid;
      if(sscanf(d->d_name, "%d", &pid) == 1 && pid != 0)
        {
        struct stat finfo;
        sprintf(fname, "/proc/%d/stat", pid);
        if(stat(fname, &finfo) == 0)
          {
          FILE* f = fopen(fname, "r");
          if(f)
            {
            size_t nread = fread(buffer, 1, KWSYSPE_PIPE_BUFFER_SIZE, f);
            buffer[nread] = '\0';
            if(nread > 0)
              {
              const char* rparen = strrchr(buffer, ')');
              int ppid;
              if(rparen && (sscanf(rparen+1, "%*s %d", &ppid) == 1))
                {
                if(ppid == process_id)
                  {

                  kwsysProcessKill(pid);
                  }
                }
              }
            fclose(f);
            }
          }
        }
      }
    closedir(procdir);
    }
  else
#endif
    {
#if defined(KWSYSPE_PS_COMMAND)

    FILE* ps = popen(KWSYSPE_PS_COMMAND, "r");


    if(ps && fscanf(ps, "%*[^\n]\n") != EOF)
      {

      int pid, ppid;
      while(fscanf(ps, KWSYSPE_PS_FORMAT, &pid, &ppid) == 2)
        {
        if(ppid == process_id)
          {

          kwsysProcessKill(pid);
          }
        }
      }


    if(ps)
      {
      pclose(ps);
      }
#endif
    }


  kill(process_id, SIGKILL);

#if defined(__APPLE__)


  kill(process_id, SIGCONT);
  kill(process_id, SIGKILL);
#endif
}
