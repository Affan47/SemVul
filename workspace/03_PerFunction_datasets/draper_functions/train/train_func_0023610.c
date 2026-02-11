utransfree (q)
     struct stransfer *q;
{
  ubuffree (q->zcmd);
  ubuffree ((char *) q->s.zfrom);
  ubuffree ((char *) q->s.zto);
  ubuffree ((char *) q->s.zuser);
  ubuffree ((char *) q->s.zoptions);
  ubuffree ((char *) q->s.ztemp);
  ubuffree ((char *) q->s.znotify);
  ubuffree ((char *) q->s.zcmd);

  utchanfree (q);
  if (q->iremote > 0)
    {
      aqTremote[q->iremote] = NULL;
      q->iremote = 0;
    }

  if (ffileisopen (q->e))
    {
      (void) ffileclose (q->e);
      q->e = EFILECLOSED;
    }

#if DEBUG > 0
  q->zcmd = NULL;
  q->s.zfrom = NULL;
  q->s.zto = NULL;
  q->s.zuser = NULL;
  q->s.zoptions = NULL;
  q->s.ztemp = NULL;
  q->s.znotify = NULL;
  q->s.zcmd = NULL;
  q->psendfn = NULL;
  q->precfn = NULL;
#endif


  if (qTtiming_rec == q)
    qTtiming_rec = NULL;

  utdequeue (q);
  utqueue (&qTavail, q, FALSE);
}
