PR_union_tc(const char* id, const char* name,
			     TypeCode_ptr discriminator_type,
			     const PR_unionMember* members,
			     ULong memberCount, Long deflt,
			     CORBA::TypeCode::_Tracker* tracker)
{
  check_static_data_is_initialised();

  TypeCode_base* indirect = 0;

  CORBA::TypeCode_ptr r = the_typecodes->find(id);
  if (r) {
    indirect = ToTcBase(r);
    if (indirect->NP_kind() == CORBA::_np_tk_indirect) {


    }
    else {
      OMNIORB_ASSERT(indirect->NP_kind() == CORBA::tk_union);
      return r;
    }
  }

  r = new TypeCode_union(id, name,
			 ToTcBase(discriminator_type),
			 members, memberCount, deflt);
  tracker->add(r);
  the_typecodes->add(id, r);
  if (indirect)
    indirect->NP_complete_recursive(ToTcBase(r), id);

  return r;
}
