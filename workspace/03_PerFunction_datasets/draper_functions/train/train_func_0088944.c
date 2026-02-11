current_member_name()
{
  CHECK_NOT_DESTROYED;
  if( pd_n_components == 0 ) throw DynamicAny::DynAny::TypeMismatch();
  if( pd_curr_index < 0 )    throw DynamicAny::DynAny::InvalidValue();

  return CORBA::string_dup(actualTc()->NP_member_name(pd_curr_index));
}
