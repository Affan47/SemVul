setLogFilename(const char* n)
{
  const char* existing = (const char*)logfilename;
  if (existing && !strcmp(existing, n)) {

    return;
  }
  FILE* f = fopen(n, "a");
  if (!f) {

    if (omniORB::trace(1)) {
      omniORB::logger l;
      l << "Unable to open log file '" << n << "'.\n";
    }
    OMNIORB_THROW(INITIALIZE, INITIALIZE_CannotOpenLogFile,
		  CORBA::COMPLETED_NO);
  }
  if ((const char*)logfilename) {

    fclose(logfile);
  }
  logfile = f;
  logfilename = n;
}
