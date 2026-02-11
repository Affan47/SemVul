operator>>= (cdrStream& s) const
{
  if (orbParameters::tcAliasExpand) {
    CORBA::TypeCode_var tc = TypeCode_base::aliasExpand(ToTcBase(get(pd_tc)));
    CORBA::TypeCode::marshalTypeCode(tc, s);
  }
  else
    CORBA::TypeCode::marshalTypeCode(get(pd_tc), s);

  if (pd_data) {
    OMNIORB_ASSERT(pd_marshal);
    pd_marshal(s, pd_data);
  }
  else if (pd_mbuf) {
    tcParser::copyMemStreamToStream_rdonly(get(pd_tc), *pd_mbuf, s);
  }
  else {
    CORBA::TCKind kind = get(pd_tc)->kind();
    if (kind == CORBA::tk_objref ||
        kind == CORBA::tk_value ||
	kind == CORBA::tk_value_box ||
	kind == CORBA::tk_abstract_interface) {


      OMNIORB_ASSERT(pd_marshal);
      pd_marshal(s, pd_data);
    }
    else {
      OMNIORB_ASSERT(kind == CORBA::tk_void || kind == CORBA::tk_null);
    }
  }
}
