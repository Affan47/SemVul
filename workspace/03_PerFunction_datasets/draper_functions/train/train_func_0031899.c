NP_value_tc(const char* id, const char* name,
			     CORBA::ValueModifier type_modifier,
			     CORBA::TypeCode_ptr concrete_base,
			     const ValueMemberSeq& members)
{
  CORBA::ULong memberCount = members.length();
  CORBA::ULong i;

  TypeCode_value::Member* new_members =
    new TypeCode_value::Member[memberCount];

  for (i=0; i < memberCount; i++) {
    new_members[i].name = CORBA::string_dup(members[i].name);
    new_members[i].type =
      TypeCode_collector::duplicateRef(ToTcBase(members[i].type));
    new_members[i].access = members[i].access;
  }

  return new TypeCode_value(id, name, type_modifier, ToTcBase(concrete_base),
			    new_members, memberCount);
}
