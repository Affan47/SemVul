_this()
{
  omniCurrent* current = omniCurrent::get();
  if (current) {
    omniCallDescriptor* call_desc = current->callDescriptor();

    if (call_desc &&
	call_desc->localId()->servant() == (omniServant*)this) {


      omniObjRef* ref = omniOrbPOACurrent::real_get_reference(call_desc);
      OMNIORB_ASSERT(ref);
      return (CORBA::Object_ptr)ref->_ptrToObjRef(CORBA::Object::_PD_repoId);
    }
  }

  throw PortableServer::POA::WrongPolicy();
}
