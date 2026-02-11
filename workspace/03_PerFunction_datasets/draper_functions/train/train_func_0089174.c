delete_values(const char* pattern)
{
  omni_tracedmutex_lock lock(pd_lock);
  CORBA::ULong bottom, top;

  if( !matchPattern(pattern, bottom, top) )
    OMNIORB_THROW(BAD_CONTEXT,
		  BAD_CONTEXT_NoMatchingProperty,
		  CORBA::COMPLETED_NO);

  CORBA::ULong nmatches = top - bottom;
  CORBA::ULong count = pd_entries.length();


  for( CORBA::ULong i = bottom; i  + nmatches < count; i++ ){
    CORBA::string_free(pd_entries[i].name);
    CORBA::string_free(pd_entries[i].value);
    pd_entries[i] = pd_entries[i + nmatches];
  }
  pd_entries.length(pd_entries.length() - nmatches);
}
