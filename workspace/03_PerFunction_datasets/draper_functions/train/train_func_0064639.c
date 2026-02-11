_ptrToInterface(const char* id)
{
  if( id == ::CosStream::Node::_PD_repoId )
    return (::CosStream::_impl_Node*) this;
  if( id == ::CosGraphs::Node::_PD_repoId )
    return (::CosGraphs::_impl_Node*) this;

  if( id == ::CosStream::Streamable::_PD_repoId )
    return (::CosStream::_impl_Streamable*) this;

  if( id == ::CosObjectIdentity::IdentifiableObject::_PD_repoId )
    return (::CosObjectIdentity::_impl_IdentifiableObject*) this;


  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::CosStream::Node::_PD_repoId) )
    return (::CosStream::_impl_Node*) this;
  if( omni::strMatch(id, ::CosGraphs::Node::_PD_repoId) )
    return (::CosGraphs::_impl_Node*) this;

  if( omni::strMatch(id, ::CosStream::Streamable::_PD_repoId) )
    return (::CosStream::_impl_Streamable*) this;

  if( omni::strMatch(id, ::CosObjectIdentity::IdentifiableObject::_PD_repoId) )
    return (::CosObjectIdentity::_impl_IdentifiableObject*) this;


  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}
