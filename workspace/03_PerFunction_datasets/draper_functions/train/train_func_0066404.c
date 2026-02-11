validateUserException(const CORBA::UserException& ex)
{


  if (pd_user_excns) {
    int size;
    const char* repoId = ex._NP_repoId(&size);

    for (int i=0; i < pd_n_user_excns; ++i) {
      if (omni::strMatch(repoId, pd_user_excns[i]))
	return;
    }
    if (omniORB::trace(1)) {
      omniORB::logger log;
      log << "WARNING -- local call raised unexpected user exception '"
	  << repoId << "'.\n";

      OMNIORB_THROW(UNKNOWN,UNKNOWN_UserException, CORBA::COMPLETED_MAYBE);
    }
  }
}
