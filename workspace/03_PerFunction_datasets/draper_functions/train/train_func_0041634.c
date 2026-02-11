userException(cdrStream& s, _OMNI_NS(IOP_C)* iop_client, const char* repoId)
{
  if ( omni::strMatch(repoId, CosTime::TimeUnavailable::_PD_repoId) ) {
    CosTime::TimeUnavailable _ex;
    _ex <<= s;
    if (iop_client) iop_client->RequestCompleted();
    throw _ex;
  }


  else {
    if (iop_client) iop_client->RequestCompleted(1);
    OMNIORB_THROW(UNKNOWN,UNKNOWN_UserException,
                  (::CORBA::CompletionStatus)s.completion());
  }
}
