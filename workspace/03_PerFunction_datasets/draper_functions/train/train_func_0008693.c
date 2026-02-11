dump(orbOptions::sequenceString& result) {
    if (omni::myPrincipalID.length() == 0)
      orbOptions::addKVString(key(),"[Null]",result);
    else {
      CORBA::String_var s(CORBA::string_alloc(omni::myPrincipalID.length()+1));
      CORBA::ULong i;
      for (i=0; i<omni::myPrincipalID.length(); i++) {
	((char*)s)[i] = omni::myPrincipalID[i];
      }
      ((char*)s)[i] = '\0';
      orbOptions::addKVString(key(),s,result);
    }
  }
