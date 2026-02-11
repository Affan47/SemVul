_ptrToObjRef(const char* id)
{
  if( id == PortableServer::ServantLocator::_PD_repoId )
    return (PortableServer::ServantLocator_ptr) this;

  if( id == PortableServer::ServantManager::_PD_repoId )
    return (PortableServer::ServantManager_ptr) this;

  if( id == CORBA::LocalObject::_PD_repoId )
    return (CORBA::LocalObject_ptr) this;

  if( id == CORBA::Object::_PD_repoId )
    return (CORBA::Object_ptr) this;

  if( omni::strMatch(id, PortableServer::ServantLocator::_PD_repoId) )
    return (PortableServer::ServantLocator_ptr) this;

  if( omni::strMatch(id, PortableServer::ServantManager::_PD_repoId) )
    return (PortableServer::ServantManager_ptr) this;

  if( omni::strMatch(id, CORBA::LocalObject::_PD_repoId) )
    return (CORBA::LocalObject_ptr) this;

  if( omni::strMatch(id, CORBA::Object::_PD_repoId) )
    return (CORBA::Object_ptr) this;

  return 0;
}
