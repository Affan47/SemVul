is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::CosNotifyChannelAdmin::SequenceProxyPushConsumer::_PD_repoId) )
    return 1;
  if( omni::ptrStrMatch(id, CosNotifyChannelAdmin::ProxyConsumer::_PD_repoId) )
    return 1;

  if( omni::ptrStrMatch(id, CosNotifyComm::SequencePushConsumer::_PD_repoId) )
    return 1;

  if( omni::ptrStrMatch(id, CosNotification::QoSAdmin::_PD_repoId) )
    return 1;

  if( omni::ptrStrMatch(id, CosNotifyFilter::FilterAdmin::_PD_repoId) )
    return 1;

  if( omni::ptrStrMatch(id, CosNotifyComm::NotifyPublish::_PD_repoId) )
    return 1;


  return 0;
}
