mgrib_settransform( Transform T )
{
  mrti(mr_identity, mr_NULL);
  mg_settransform( T );
  TmConcat(_mgc->xstk->T, _mgc->W2S, _mgc->O2S);
  if(T != TM_IDENTITY)
    mgrib_printmatrix(T);
}
