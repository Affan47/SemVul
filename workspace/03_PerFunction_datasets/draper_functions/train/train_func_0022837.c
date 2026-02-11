cfpclose_def(FILE *pp,char *defines,char *elsedef)

{ int fd, status, wait_result;
  pid_t pid;

Debug("cfpclose_def(pp)\n");

if (CHILD == NULL)
   {
   return -1;
   }

fd = fileno(pp);

if ((pid = CHILD[fd]) == 0)
   {
   return -1;
   }

CHILD[fd] = 0;

if (fclose(pp) == EOF)
   {
   return -1;
   }

Debug("cfpopen_def - Waiting for process %d\n",pid);

#ifdef HAVE_WAITPID

while(waitpid(pid,&status,0) < 0)
   {
   if (errno != EINTR)
      {
      Verbose("Waitpid failed - %d\n",errno);
      return -1;
      }
   }

if (status == 0)
   {
   AddMultipleClasses(defines);
   }
else
   {
   AddMultipleClasses(elsedef);
   Debug("Child returned status %d\n",status);
   }

return status;

#else

 while ((wait_result = wait(&status)) != pid)
    {
    if (wait_result <= 0)
       {
       snprintf(OUTPUT,CF_BUFSIZE,"Wait for child failed\n");
       CfLog(cfinform,OUTPUT,"wait");
       return -1;
       }
    }

 if (WIFSIGNALED(status))
    {
    return -1;
    }

 if (! WIFEXITED(status))
    {
    return -1;
    }

 if (WEXITSTATUS(status) == 0)
    {
    AddMultipleClasses(defines);
    }
 else
    {
    AddMultipleClasses(elsedef);
    }

 return (WEXITSTATUS(status));

#endif
}
