ddf_WriteInputIncidence(FILE *f, ddf_PolyhedraPtr poly)
{
  ddf_SetFamilyPtr I;

  if (poly->AincGenerated==ddf_FALSE) ddf_ComputeAinc(poly);
  switch (poly->representation) {
  case ddf_Inequality:
    fprintf(f,"icd_file: Incidence of inequalities and generators\n");
    break;

  case ddf_Generator:
   fprintf(f,"ecd_file: Incidence of generators and inequalities\n");
    break;

  default:
    break;
  }

  I=ddf_CopyInputIncidence(poly);
  ddf_WriteSetFamilyCompressed(f,I);
  ddf_FreeSetFamily(I);
}
