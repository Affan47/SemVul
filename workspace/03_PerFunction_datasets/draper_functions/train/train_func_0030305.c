initialize_acl(void)
{
	if (!IsBootstrapProcessingMode())
	{


		CacheRegisterSyscacheCallback(AUTHMEMROLEMEM,
									  RoleMembershipCacheCallback,
									  (Datum) 0);
	}
}
