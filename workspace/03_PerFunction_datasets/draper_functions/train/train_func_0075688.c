copy()
{
  CHECK_NOT_DESTROYED;
  DynValueImpl* da = new DynValueImpl(TypeCode_collector::duplicateRef(tc()),
				      DYNANY_ROOT);
  try {
    da->assign(this);
  }
  catch(...) {
    da->_NP_decrRefCount();
    throw;
  }
  return da;
}
