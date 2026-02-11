operator<<=(Object_ptr obj)
{
  if (!CORBA::Object::_PR_is_valid(obj)) {
    OMNIORB_THROW(BAD_PARAM,BAD_PARAM_InvalidObjectRef,CORBA::COMPLETED_NO);
  }
#if 1


  const char* repoid = CORBA::Object::_PD_repoId;
  const char* name   = "";
  if (!CORBA::is_nil(obj))
    repoid = obj->_PR_getobj()->_mostDerivedRepoId();
  CORBA::TypeCode_var tc = CORBA::TypeCode::NP_interface_tc(repoid,name);
#else
  CORBA::TypeCode_ptr tc = CORBA::_tc_Object;
#endif

  CORBA::Object_ptr no = CORBA::Object::_duplicate(obj);
  PR_insert(tc, marshalObject_fn, deleteObject_fn, no->_PR_getobj());
}
