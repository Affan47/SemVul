delete_identique_atomic_standard_orb(TypeBasisBySym BasisBySym[MAXSYM],gint maxsym)
{
 gint i;
 gint j;
 CGTF* tmp = NULL;
 gint naorbs = 1;
 gboolean* todelete;

 if(NAOrb<1)
	 return;

 tmp = g_malloc(NAOrb*sizeof(CGTF));
 todelete = g_malloc(NAOrb*sizeof(gboolean));
 tmp[0] = AOrb[0];
 todelete[0] = FALSE;
 for(i=1;i<NAOrb;i++)
 {
 	todelete[i] = TRUE;
 	for(j=0;j<i;j++)
		if(CGTFEqCGTF(&tmp[j],&AOrb[i]))
			break;
	if(j!=i)
		continue;
 	todelete[i] = FALSE;
	tmp[naorbs]=AOrb[i];
	naorbs++;
 }
  for(i=0;i<NAOrb;i++)
	if(todelete[i])
		g_free(AOrb[i].Gtf);
  if(AOrb)
	  g_free(AOrb);
 NAOrb = naorbs;
 AOrb = tmp;
 if(SAOrb) g_free(SAOrb);
 SAOrb = NULL;

}
