n_params( EnvT* e)
  {
    EnvUDT* caller = static_cast<EnvUDT*>(e->Caller());
    if( caller == NULL) return new DLongGDL( 0);
    DLong nP = caller->NParam();
    if( caller->IsObject())
      return new DLongGDL( nP-1);
    return new DLongGDL( nP);
  }
