FAcceptAspect(obj1, asp, obj2)
int obj1, asp, obj2;
{
  int fSupp;

  if (ignorea(asp))
    return fFalse;

  if (us.nRel > rcDual && FCusp(obj1) && FCusp(obj2))
    return fFalse;

  if (FStar(obj1) && FStar(obj2))
    return fFalse;

  if (us.fSmartCusp) {


    if ((FMinor(obj1) || FMinor(obj2)) && asp > aCon)
      return fFalse;


    fSupp = (asp == aOpp || asp == aSex || asp == aSSx || asp == aSes);
    if ((FAngle(obj1) || FAngle(obj2)) &&
      (fSupp || (asp == aSqu &&
      (obj1 == oDes || obj2 == oDes || obj1 == oNad || obj2 == oNad))))
      return fFalse;


    if (fSouthNode) {
      if (((obj1 == oNod || obj2 == oNod) && fSupp) ||
        ((obj1 == oSou || obj2 == oSou) && (fSupp || asp == aSqu)))
        return fFalse;
    }
  }
  return fTrue;
}
