add_object_to_etherealisation_queue(omniObjTableEntry* entry,
				PortableServer::ServantActivator_ptr sa,
				int cleanup_in_progress, int detached)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omni::internalLock, 0);
  OMNIORB_ASSERT(entry);

  omniEtherealiser* e = new omniEtherealiser(entry, sa, this,
					     entry->key() + pd_poaIdSize,
					     entry->keysize() - pd_poaIdSize,
					     cleanup_in_progress);

  if( !detached )  detached_object();

  omni::internalLock->lock();

  if( !pd_servant_activator_queue )
    pd_servant_activator_queue = new omniServantActivatorTaskQueue;

  e->set_is_last(entry->servant()->_activations().empty());

  pd_servant_activator_queue->insert(e);

  omni::internalLock->unlock();


}
