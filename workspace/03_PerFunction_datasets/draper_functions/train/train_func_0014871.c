DynSequenceImpl(TypeCode_base* tc, CORBA::Boolean is_root)
  : DynAnyConstrBase(tc, dt_seq, is_root)
{
  pd_bound = actualTc()->NP_length();
}
