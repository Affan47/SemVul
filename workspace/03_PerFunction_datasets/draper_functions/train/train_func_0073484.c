rebin_fun( EnvT* e)
  {
    SizeT nParam = e->NParam( 2);

    BaseGDL* p0 = e->GetNumericParDefined( 0);

    SizeT rank = p0->Rank();

    if( rank == 0)
      e->Throw( "Expression must be an array in this context: "+
		e->GetParString(0));

    SizeT resDimInit[ MAXRANK];

    DLongGDL* p1 = e->GetParAs<DLongGDL>(1);
    if (p1->Rank() > 0 && nParam > 2)
      e->Throw("The new dimensions must either be specified as an array or as a set of scalars.");
    SizeT np = p1->Rank() == 0 ? nParam : p1->N_Elements() + 1;

    for( SizeT p=1; p<np; ++p)
      {
	DLong newDim;
	if (p1->Rank() == 0) e->AssureLongScalarPar( p, newDim);
        else newDim = (*p1)[p - 1];

	if( newDim <= 0)
	  e->Throw( "Array dimensions must be greater than 0.");

	if( rank >= p)
	  {
	    SizeT oldDim = p0->Dim( p-1);

	    if( newDim > oldDim)
	      {
		if( (newDim % oldDim) != 0)
		  e->Throw( "Result dimensions must be integer factor "
			    "of original dimensions.");
	      }
	    else
	      {
		if( (oldDim % newDim) != 0)
		  e->Throw( "Result dimensions must be integer factor "
			    "of original dimensions.");
	      }
	  }

	resDimInit[ p-1] = newDim;
      }

    dimension resDim( resDimInit, np-1);

    static int sampleIx = e->KeywordIx( "SAMPLE");
    bool sample = e->KeywordSet( sampleIx);

    return p0->Rebin( resDim, sample);
  }
