newcodelistelem(Specialcontext *specialcontext,
                            unsigned long smallerval,
                            unsigned long largerval,
                            const Enumcodeatposition *ecp)
{
  if (smallerval < largerval)
  {
    unsigned long distance = largerval - smallerval;

    if (distance > (unsigned long) (ecp->prefixlength-1))
    {
      distance = (unsigned long) (ecp->prefixlength-1);
    }
    specialcontext->maxprefixindex = (unsigned int) distance;
    if (ecp->moveforward)
    {
      specialcontext->position = ecp->totallength - smallerval;
    } else
    {
      specialcontext->position = largerval;
    }
    gt_assert(specialcontext->position >=
              (unsigned long) specialcontext->maxprefixindex);
    return true;
  }
  return false;
}
