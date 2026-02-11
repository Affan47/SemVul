addKVBoolean(const char* key, CORBA::Boolean value,
			 orbOptions::sequenceString& result) {

  CORBA::String_var kv;
  CORBA::ULong l;

  l = strlen(key) + 4;
  kv = CORBA::string_alloc(l);
  sprintf(kv,"%s = %s",key,(value ? "1" : "0"));

  l = result.length();
  result.length(l+1);
  result[l] = kv._retn();
}
