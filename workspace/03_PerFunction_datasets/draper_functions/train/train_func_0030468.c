CShift( DLong s[MAXRANK]) const
{

  DStructGDL* sh = new DStructGDL( Desc(), dim);

  SizeT nDim = Rank();
  SizeT nEl = N_Elements();

  SizeT nTags = NTags();

  SizeT  stride[ MAXRANK + 1];
  dim.Stride( stride, nDim);

  long  srcIx[ MAXRANK+1];
  long  dstIx[ MAXRANK+1];
  SizeT dim_stride[ MAXRANK];
  for( SizeT aSp=0; aSp<nDim; ++aSp)
    {
      srcIx[ aSp] = 0;
      if( s[ aSp] >= 0)
	dstIx[ aSp] = s[ aSp] % dim[ aSp];
      else
	dstIx[ aSp] = -(-s[aSp] % dim[ aSp]);
      if( dstIx[ aSp] < 0) dstIx[ aSp] += dim[ aSp];

      dim_stride[ aSp] = dim[ aSp] * stride[ aSp];
    }
  srcIx[ nDim] = dstIx[ nDim] = 0;

  SizeT dstLonIx = dstIx[ 0];
  for( SizeT rSp=1; rSp<nDim; ++rSp)
    dstLonIx += dstIx[ rSp] * stride[ rSp];


  for( SizeT a=0; a<nEl; ++srcIx[0],++dstIx[0], ++dstLonIx, ++a)
    {
      for( SizeT aSp=0; aSp<nDim;)
	{
	  if( dstIx[ aSp] >= dim[ aSp])
	    {

	      dstIx[ aSp] = 0;
	      dstLonIx -= dim_stride[ aSp];
	    }
	  if( srcIx[ aSp] < dim[ aSp]) break;

	  srcIx[ aSp] = 0;
	  ++srcIx[ ++aSp];
	  ++dstIx[ aSp];
	  dstLonIx += stride[ aSp];
	}

      for( SizeT t=0; t<nTags; ++t)
	*sh->GetTag( t, dstLonIx) = *GetTag( t, a);

    }

  return sh;
}
