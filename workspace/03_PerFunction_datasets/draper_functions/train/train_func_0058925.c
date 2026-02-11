decode_prepare(int fbucket, int nbucket, IW44Image::Block &blk)
{
  int bbstate = 0;
  char *cstate = coeffstate;
  if (fbucket)
    {

      for (int buckno=0; buckno<nbucket; buckno++, cstate+=16)
        {
          int bstatetmp = 0;
          const short *pcoeff = blk.data(fbucket+buckno);
          if (! pcoeff)
            {

              bstatetmp = UNK;
            }
          else
            {
              for (int i=0; i<16; i++)
                {
                  int cstatetmp = UNK;
                  if (pcoeff[i])
                    cstatetmp = ACTIVE;
                  cstate[i] = cstatetmp;
                  bstatetmp |= cstatetmp;
                }
            }
          bucketstate[buckno] = bstatetmp;
          bbstate |= bstatetmp;
        }
    }
  else
    {

      const short *pcoeff = blk.data(0);
      if (! pcoeff)
        {

          bbstate = UNK;
        }
      else
        {
          for (int i=0; i<16; i++)
            {
              int cstatetmp = cstate[i];
              if (cstatetmp != ZERO)
                {
                  cstatetmp = UNK;
                  if (pcoeff[i])
                    cstatetmp = ACTIVE;
                }
              cstate[i] = cstatetmp;
              bbstate |= cstatetmp;
            }
        }
      bucketstate[0] = bbstate;
    }
  return bbstate;
}
