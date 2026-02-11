dump_TAG_OMNIORB_UNIX_TRANS(const IOP::TaggedComponent& c) {

  OMNIORB_ASSERT(c.tag == IOP::TAG_OMNIORB_UNIX_TRANS);
  cdrEncapsulationStream e(c.component_data.get_buffer(),
			   c.component_data.length(),1);

  CORBA::String_var host;
  host = e.unmarshalRawString();
  CORBA::String_var filename;
  filename = e.unmarshalRawString();

  const char* format = "TAG_OMNIORB_UNIX_TRANS %s %s";
  CORBA::String_var outstr;
  CORBA::ULong len = strlen(format) + strlen(host) + strlen(filename);
  outstr = CORBA::string_alloc(len);
  sprintf(outstr,format,(const char*)host,(const char*)filename);
  return outstr._retn();

}
