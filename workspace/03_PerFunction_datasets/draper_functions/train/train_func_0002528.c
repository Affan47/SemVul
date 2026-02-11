lrs_close (const char *name)
{
#ifdef UNUSED_BY_GAMBIT
  fprintf (lrs_ofp, "\n*%s", name);
  fprintf (lrs_ofp, TITLE);
  fprintf (lrs_ofp, LRS_VERSION);
  fprintf (lrs_ofp, "(");
  fprintf (lrs_ofp, BIT);
  fprintf (lrs_ofp, ",");
  fprintf (lrs_ofp, ARITH);
  fprintf (lrs_ofp, ")");
#endif

#ifdef MP

#endif

#ifdef TIMES

#endif


  fclose (lrs_ifp);
  if (lrs_ofp != stdout)
    fclose (lrs_ofp);
}
