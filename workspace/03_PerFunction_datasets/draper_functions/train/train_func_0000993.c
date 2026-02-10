set_elements(const DynamicAny::AnySeq& as)
{
  CHECK_NOT_DESTROYED;

  if( as.length() != pd_n_components )
    throw DynamicAny::DynAny::InvalidValue();

  for( unsigned i = 0; i < pd_n_components; i++ ) {
    if( !component_from_any(i, as[i]) )
      throw DynamicAny::DynAny::TypeMismatch();
  }
}
