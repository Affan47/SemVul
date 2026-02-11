NP_complete_recursive(TypeCode_base* tc, const char* repoId)
{
  if (!pd_complete) {
    pd_complete = 1;

    for( CORBA::ULong i = 0; i < pd_nmembers; i++ ) {
      pd_complete = pd_complete &&
	ToTcBase(pd_members[i].type)->NP_complete_recursive(tc, repoId);
    }
  }
  return pd_complete;
}
