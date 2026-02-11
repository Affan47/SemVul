_openchild (const char *command, FILE ** fto, FILE ** ffrom)
{
  int i;
  int pid;
  int pdto[2];
  int pdfrom[2];

  if (__pipe (pdto) < 0)
    goto error1;
  if (__pipe (pdfrom) < 0)
    goto error2;
  switch (pid = __fork ())
    {
    case -1:
      goto error3;

    case 0:


      __close (0);
      __dup (pdto[0]);
      __close (1);
      __dup (pdfrom[1]);
      fflush (stderr);
      for (i = _rpc_dtablesize () - 1; i >= 3; i--)
	__close (i);
      fflush (stderr);
      execlp (command, command, NULL);
      perror ("exec");
      _exit (~0);

    default:


      *fto = __fdopen (pdto[1], "w");
      __close (pdto[0]);
      *ffrom = __fdopen (pdfrom[0], "r");
      __close (pdfrom[1]);
      break;
    }
  return pid;


error3:
  __close (pdfrom[0]);
  __close (pdfrom[1]);
error2:
  __close (pdto[0]);
  __close (pdto[1]);
error1:
  return -1;
}
