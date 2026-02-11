replicate( EnvT* e)
  {
    SizeT nParam=e->NParam();
    if( nParam < 2)
      e->Throw( "Incorrect number of arguments.");
    dimension dim;
    arr( e, dim, 1);

    BaseGDL* p0=e->GetParDefined( 0);
    if( !p0->Scalar())
      e->Throw(	"Expression must be a scalar in this context: "+
		e->GetParString(0));

    return p0->New( dim, BaseGDL::INIT);
  }
