fjreceive_data (qconn, cineed, pcrec, ctimeout, freport)
     struct sconnection *qconn;
     size_t cineed;
     size_t *pcrec;
     int ctimeout;
     boolean freport;
{
  int iprecendstart;
  size_t cjneed;
  size_t crec;
  int cnew;

  iprecendstart = iPrecend;


  if (! fjprocess_data (&cjneed))
    return FALSE;


  do
    {
      int iprecendhold;
      size_t cneed;

      if (cjneed > cineed)
	cneed = cjneed;
      else
	cneed = cineed;


      iprecendhold = iPrecend;
      iPrecend = iJrecend;
      if (! freceive_data (qconn, cneed, &crec, ctimeout, freport))
	return FALSE;
      iJrecend = iPrecend;
      iPrecend = iprecendhold;


      if (! fjprocess_data (&cjneed))
	return FALSE;

      cnew = iPrecend - iprecendstart;
      if (cnew < 0)
	cnew += CRECBUFLEN;

      if ((size_t) cnew > cineed)
	cineed = 0;
      else
	cineed -= cnew;

      --ctimeout;
    }
  while (cnew == 0 && crec > 0 && ctimeout > 0);

  DEBUG_MESSAGE1 (DEBUG_PROTO, "fjreceive_data: Got %d decoded bytes",
		  cnew);

  *pcrec = cnew;
  return TRUE;
}
