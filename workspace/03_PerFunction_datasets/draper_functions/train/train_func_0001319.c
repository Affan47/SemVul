sptrans_delete(SPTRANS *sptrans)
{
  if ( sptrans )
    {
      if ( sptrans->trig ) { free(sptrans->trig);  sptrans->trig = NULL; }
      if ( sptrans->poli ) { free(sptrans->poli);  sptrans->poli = NULL; }
      if ( sptrans->pold ) { free(sptrans->pold);  sptrans->pold = NULL; }
      if ( sptrans->pol2 ) { free(sptrans->pol2);  sptrans->pol2 = NULL; }
      if ( sptrans->pol3 ) { free(sptrans->pol3);  sptrans->pol3 = NULL; }
      if ( sptrans->coslat  ) { free(sptrans->coslat);   sptrans->coslat = NULL; }
      if ( sptrans->rcoslat ) { free(sptrans->rcoslat);  sptrans->rcoslat = NULL; }

      free(sptrans); sptrans = NULL;
    }
}
