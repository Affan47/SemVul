ResourceOwnerForgetLock(ResourceOwner owner, LOCALLOCK *locallock)
{
	int			i;

	if (owner->nlocks > MAX_RESOWNER_LOCKS)
		return;

	Assert(owner->nlocks > 0);
	for (i = owner->nlocks - 1; i >= 0; i--)
	{
		if (locallock == owner->locks[i])
		{
			owner->locks[i] = owner->locks[owner->nlocks - 1];
			owner->nlocks--;
			return;
		}
	}
	elog(ERROR, "lock reference %p is not owned by resource owner %s",
		 locallock, owner->name);
}
