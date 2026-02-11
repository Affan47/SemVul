get_elements_as_dyn_any()
{
  CHECK_NOT_DESTROYED;
  DynamicAny::DynAnySeq* as = new DynamicAny::DynAnySeq();
  as->length(pd_n_components);

  createComponent(0);


  for( unsigned i = 0; i < pd_n_components; i++ ) {
    pd_components[i]->_NP_incrRefCount();
    (*as)[i] = pd_components[i];
  }
  return as;
}
