dump_TAG_OMNIORB_BIDIR(const IOP::TaggedComponent& c) {

  OMNIORB_ASSERT(c.tag == IOP::TAG_OMNIORB_BIDIR);
  cdrEncapsulationStream e(c.component_data.get_buffer(),
			   c.component_data.length(),1);

  CORBA::String_var sendfrom;
  sendfrom = e.unmarshalRawString();
  CORBA::String_var outstr;
  CORBA::ULong len = sizeof("TAG_OMNIORB_BIDIR ")+strlen(sendfrom);
  outstr = CORBA::string_alloc(len);
  sprintf(outstr,"%s %s","TAG_OMNIORB_BIDIR",(const char*)sendfrom);
  return outstr._retn();
}
