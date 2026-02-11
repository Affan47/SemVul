struct_assign_pro( EnvT* e)
  {
    SizeT nParam=e->NParam( 2);

    DStructGDL* source = e->GetParAs<DStructGDL>(0);
    DStructGDL* dest   = e->GetParAs<DStructGDL>(1);

    static int nozeroIx = e->KeywordIx("NOZERO");
    bool nozero = e->KeywordSet( nozeroIx);

    static int verboseIx = e->KeywordIx("VERBOSE");
    bool verbose = e->KeywordSet( verboseIx);

    string sourceName = (*source).Desc()->Name();

    SizeT nTags = 0;


    SizeT nElements = source->N_Elements();
    SizeT nDestElements = dest->N_Elements();
    if( nElements > nDestElements)
      nElements = nDestElements;


    if( !nozero)
       (*dest).Clear();

    nTags = (*source).Desc()->NTags();


    for(int t=0; t < nTags; ++t)
      {
	string sourceTagName = (*source).Desc()->TagName(t);
	int ix = (*dest).Desc()->TagIndex( sourceTagName );
	if( ix >= 0)
	  {
	    SizeT nTagElements = source->GetTag( t)->N_Elements();
	    SizeT nTagDestElements = dest->GetTag( ix)->N_Elements();

	    if( verbose)
	      {
		if( nTagElements > nTagDestElements)
		  Warning( "STRUCT_ASSIGN: " + sourceName +
			   " tag " + sourceTagName +
			   " is longer than destination. "
			   "The end will be clipped.");
		else if( nTagElements < nTagDestElements)
		  Warning( "STRUCT_ASSIGN: " + sourceName +
			   " tag " + sourceTagName +
			   " is shorter than destination. "
			   "The end will be zero filled.");
	      }

	    if( nTagElements > nTagDestElements)
		nTagElements = nTagDestElements;

	    for( SizeT a=0; a< nElements; ++a)
	      dest->GetTag( ix, a)->Assign( source->GetTag( t, a), nTagElements);
	  }
	else
	  if(verbose)
	    Warning( "STRUCT_ASSIGN: Destination lacks " + sourceName +
		     " tag " + sourceTagName + ". Not copied.");
      }
  }
