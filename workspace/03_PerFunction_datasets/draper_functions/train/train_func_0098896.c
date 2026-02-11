SetSessionAuthorization(Oid userid, bool is_superuser)
{

	AssertState(OidIsValid(AuthenticatedUserId));

	if (userid != AuthenticatedUserId &&
		!AuthenticatedUserIsSuperuser)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to set session authorization")));

	SetSessionUserId(userid, is_superuser);

	SetConfigOption("is_superuser",
					is_superuser ? "on" : "off",
					PGC_INTERNAL, PGC_S_OVERRIDE);
}
