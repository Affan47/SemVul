aclequal(const Acl *left_acl, const Acl *right_acl)
{

	if (left_acl == NULL || ACL_NUM(left_acl) == 0)
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return true;
		else
			return false;
	}
	else
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return false;
	}

	if (ACL_NUM(left_acl) != ACL_NUM(right_acl))
		return false;

	if (memcmp(ACL_DAT(left_acl),
			   ACL_DAT(right_acl),
			   ACL_NUM(left_acl) * sizeof(AclItem)) == 0)
		return true;

	return false;
}
