obj_destroy( EnvT* e)
  {
    StackGuard<EnvStackT> guard( e->Interpreter()->CallStack());

    int nParam=e->NParam();
    if( nParam == 0) return;

    BaseGDL* p= e->GetParDefined( 0);

    if( p->Type() != GDL_OBJ)
      e->Throw( "Parameter must be an object in"
		" this context: "+
		e->GetParString(0));
    DObjGDL* op= static_cast<DObjGDL*>(p);

    SizeT nEl=op->N_Elements();
    for( SizeT i=0; i<nEl; i++)
      {
	DObj actID=(*op)[i];
	e->ObjCleanup( actID);
      }
  }
