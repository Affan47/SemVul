ParallelFindAndVerifyFilesPromises(struct Promise *pp)

{ pid_t child = 1;
  int background = GetBooleanConstraint("background",pp);

#ifdef MINGW

if (background)
   {
   CfOut(cf_verbose, "", "Background processing of files promises is not supported on Windows");
   }

FindAndVerifyFilesPromises(pp);

#else

if (background && (CFA_BACKGROUND < CFA_BACKGROUND_LIMIT))
   {
   CFA_BACKGROUND++;
   CfOut(cf_verbose,"","Spawning new process...\n");
   child = fork();

   if (child == 0)
      {
      ALARM_PID = -1;
      AM_BACKGROUND_PROCESS = true;
      }
   else
      {
      AM_BACKGROUND_PROCESS = false;
      }
   }
else if (CFA_BACKGROUND >= CFA_BACKGROUND_LIMIT)
   {
   CfOut(cf_verbose,""," !> Promised parallel execution promised but exceeded the max number of promised background tasks, so serializing");
   }

if (child == 0 || !background)
   {
   FindAndVerifyFilesPromises(pp);
   }

#endif
}
