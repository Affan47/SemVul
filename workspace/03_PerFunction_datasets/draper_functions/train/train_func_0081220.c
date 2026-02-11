FDKaacEnc_calcSingleSpecPe(INT scf, FIXP_DBL sfbConstPePart, FIXP_DBL nLines)
{
  FIXP_DBL specPe = FL2FXCONST_DBL(0.0f);
  FIXP_DBL ldRatio;
  FIXP_DBL scfFract;

  scfFract = (FIXP_DBL)(scf << (DFRACT_BITS-1-AS_PE_FAC_SHIFT));

  ldRatio = sfbConstPePart - fMult(FL2FXCONST_DBL(0.375f),scfFract);

  if (ldRatio >= PE_C1) {
    specPe = fMult(FL2FXCONST_DBL(0.7f),fMult(nLines,ldRatio));
  }
  else {
    specPe = fMult(FL2FXCONST_DBL(0.7f),fMult(nLines,(PE_C2 + fMult(PE_C3,ldRatio))));
  }

  return specPe;
}
