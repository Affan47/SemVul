activate()
{
  CHECK_NOT_NIL();

  omni_tracedmutex_lock sync(pm_lock);

  if( pd_state == INACTIVE )  throw AdapterInactive();
  if( pd_state == ACTIVE   )  return;

  pd_state = ACTIVE;

  for( CORBA::ULong i = 0; i < pd_poas.length(); i++ )
    pd_poas[i]->pm_change_state(pd_state);
}
