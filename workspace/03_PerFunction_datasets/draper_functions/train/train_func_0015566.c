heap_gc( EnvT* e)
  {
    static SizeT objIx = e->KeywordIx( "OBJ");
    static SizeT ptrIx = e->KeywordIx( "PTR");
    static SizeT verboseIx = e->KeywordIx( "VERBOSE");
    bool doObj = e->KeywordSet( objIx);
    bool doPtr = e->KeywordSet( ptrIx);
    bool verbose =  e->KeywordSet( verboseIx);
    if( !doObj && !doPtr)
      doObj = doPtr = true;

    e->HeapGC( doPtr, doObj, verbose);
  }
