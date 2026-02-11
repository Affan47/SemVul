initialise_poa()
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(poa_lock, 1);
  OMNIORB_ASSERT(!theRootPOA);


  omniObjAdapter::initialise();


  omniOrbPOA::Policies policy;
  policy.threading = omniOrbPOA::TP_ORB_CTRL;
  policy.transient = 1;
  policy.multiple_id = 0;
  policy.user_assigned_id = 0;
  policy.retain_servants = 1;
  policy.req_processing = omniOrbPOA::RPP_ACTIVE_OBJ_MAP;
  policy.implicit_activation = 1;
  policy.bidirectional_accept = 0;
  policy.local_shortcut = 0;

  omniOrbPOAManager* manager = new omniOrbPOAManager();

  CORBA::PolicyList pl(1);
  pl.length(1);
  pl[0] = new PortableServer::ImplicitActivationPolicy(PortableServer::
						       IMPLICIT_ACTIVATION);

  theRootPOA = new omniOrbPOA("RootPOA", manager, policy, pl, 0);
  manager->gain_poa(theRootPOA);
  theRootPOA->adapterActive();
}
