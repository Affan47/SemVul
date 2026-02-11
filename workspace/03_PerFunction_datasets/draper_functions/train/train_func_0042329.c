apme_nextLimdfsstate(const Limdfsconstinfo *mt,
                                 DECLAREPTRDFSSTATE(aliasoutcol),
                                 GT_UNUSED unsigned long currentdepth,
                                 GtUchar currentchar,
                                 const DECLAREPTRDFSSTATE(aliasincol))
{
  unsigned long Eq = 0, Xv, Xh, Ph, Mh,
                backmask,
                idx,
                score;
  ApmeoveridxLimdfsstate *outcol = (ApmeoveridxLimdfsstate *) aliasoutcol;
  const ApmeoveridxLimdfsstate *incol =
                                    (const ApmeoveridxLimdfsstate *) aliasincol;
  const ApmeoveridxLimdfsconstinfo *mti =
                                        (const ApmeoveridxLimdfsconstinfo *) mt;

  gt_assert(incol->maxleqk != UNDEFMAXLEQK);
  gt_assert(mti->maxintervalwidth > 0 || incol->maxleqk != SUCCESSMAXLEQK);
  gt_assert(currentchar != (GtUchar) SEPARATOR);
  if (currentchar != (GtUchar) WILDCARD)
  {
    Eq = mti->eqsvector[(unsigned long) currentchar];
  }
  Xv = Eq | incol->Mv;
  Xh = (((Eq & incol->Pv) + incol->Pv) ^ incol->Pv) | Eq;

  Ph = incol->Mv | ~ (Xh | incol->Pv);
  Mh = incol->Pv & Xh;

  Ph = (Ph << 1) | 1UL;
  outcol->Pv = (Mh << 1) | ~ (Xv | Ph);
  outcol->Mv = Ph & Xv;
  backmask = 1UL << incol->maxleqk;
  if (Eq & backmask || Mh & backmask)
  {
    outcol->maxleqk = incol->maxleqk + 1UL;
    outcol->lastdistvalue = incol->lastdistvalue;
  } else
  {
    if (Ph & backmask)
    {
      score = mti->maxdistance+1;
      outcol->maxleqk = UNDEFMAXLEQK;
      if (incol->maxleqk > 0)
      {
        for (idx = incol->maxleqk - 1, backmask >>= 1;
             ;
             backmask >>= 1)
        {
          if (outcol->Pv & backmask)
          {
            score--;
            if (score <= mti->maxdistance)
            {
              outcol->maxleqk = idx;
              outcol->lastdistvalue = score;
              break;
            }
          } else
          {
            if (outcol->Mv & backmask)
            {
              score++;
            }
          }
          if (idx > 0)
          {
            idx--;
          } else
          {
            break;
          }
        }
      }
    } else
    {
      outcol->maxleqk = incol->maxleqk;
      outcol->lastdistvalue = incol->lastdistvalue;
    }
  }
#ifdef SKDEBUG
  verifycolumnvalues(mti,outcol,currentdepth);
#endif
}
