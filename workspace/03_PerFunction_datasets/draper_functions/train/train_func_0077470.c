is_member_of_role_nosuper(Oid member, Oid role)
{

	if (member == role)
		return true;


	return list_member_oid(roles_is_member_of(member), role);
}
