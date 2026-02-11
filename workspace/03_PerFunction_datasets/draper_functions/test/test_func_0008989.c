prepareSequenceRead(CORBA::TCKind kind)
{
  if (pd_curr_index < 0)
    throw DynamicAny::DynAny::InvalidValue();

  const TypeCode_base* ctc;
  ctc = TypeCode_base::NP_expand(nthComponentTC(pd_curr_index));
  CORBA::TCKind k = ctc->NP_kind();

  if ((k == CORBA::tk_sequence || k == CORBA::tk_array) &&
      TypeCode_base::NP_expand(ctc->NP_content_type())->NP_kind() == kind) {
    return SEQ_COMPONENT;
  }
  throw DynamicAny::DynAny::TypeMismatch();
#ifdef NEED_DUMMY_RETURN
  return SEQ_COMPONENT;
#endif
}
