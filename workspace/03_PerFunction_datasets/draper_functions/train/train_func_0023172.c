GetOrb(obj1, obj2, asp)
int obj1, obj2, asp;
{
  real orb, r;

  orb = rAspOrb[asp];
  r = obj1 > oNorm ? StarOrb : rObjOrb[obj1];
  orb = Min(orb, r);
  r = obj2 > oNorm ? StarOrb : rObjOrb[obj2];
  orb = Min(orb, r);
  if (obj1 <= oNorm && obj2 <= oNorm) {
    orb += rObjAdd[obj1];
    orb += rObjAdd[obj2];
  if (us.fParallel)
    orb = orb / CoeffPar;
  else if (us.nRel <= rcDual || us.fTransitInf || us.fTransitInf)
    orb = orb /CoeffComp;
  }
  return orb;
}
