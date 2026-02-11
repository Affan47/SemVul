FixHoleLinkage(OutRec *outRec)
{
  OutRec *tmp;
  if (outRec->bottomPt)
    tmp = m_PolyOuts[outRec->bottomPt->idx]->FirstLeft;
  else
    tmp = outRec->FirstLeft;
  if (outRec == tmp) throw clipperException("HoleLinkage error");

  if (tmp)
  {
    if (tmp->AppendLink) tmp = FindAppendLinkEnd(tmp);
    if (tmp == outRec) tmp = 0;
    else if (tmp->isHole)
    {
      FixHoleLinkage(tmp);
      tmp = tmp->FirstLeft;
    }
  }
  outRec->FirstLeft = tmp;
  if (!tmp) outRec->isHole = false;
  outRec->AppendLink = 0;
}
