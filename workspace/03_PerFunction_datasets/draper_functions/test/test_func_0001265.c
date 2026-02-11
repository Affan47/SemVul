_ptrToInterface(const char* id)
{
  if( id == ::CosNotifyChannelAdmin::ConsumerAdmin::_PD_repoId )
    return (::CosNotifyChannelAdmin::_impl_ConsumerAdmin*) this;
  if( id == ::CosNotification::QoSAdmin::_PD_repoId )
    return (::CosNotification::_impl_QoSAdmin*) this;

  if( id == ::CosNotifyComm::NotifySubscribe::_PD_repoId )
    return (::CosNotifyComm::_impl_NotifySubscribe*) this;

  if( id == ::CosNotifyFilter::FilterAdmin::_PD_repoId )
    return (::CosNotifyFilter::_impl_FilterAdmin*) this;

  if( id == ::CosEventChannelAdmin::ConsumerAdmin::_PD_repoId )
    return (::CosEventChannelAdmin::_impl_ConsumerAdmin*) this;


  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::CosNotifyChannelAdmin::ConsumerAdmin::_PD_repoId) )
    return (::CosNotifyChannelAdmin::_impl_ConsumerAdmin*) this;
  if( omni::strMatch(id, ::CosNotification::QoSAdmin::_PD_repoId) )
    return (::CosNotification::_impl_QoSAdmin*) this;

  if( omni::strMatch(id, ::CosNotifyComm::NotifySubscribe::_PD_repoId) )
    return (::CosNotifyComm::_impl_NotifySubscribe*) this;

  if( omni::strMatch(id, ::CosNotifyFilter::FilterAdmin::_PD_repoId) )
    return (::CosNotifyFilter::_impl_FilterAdmin*) this;

  if( omni::strMatch(id, ::CosEventChannelAdmin::ConsumerAdmin::_PD_repoId) )
    return (::CosEventChannelAdmin::_impl_ConsumerAdmin*) this;


  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}
