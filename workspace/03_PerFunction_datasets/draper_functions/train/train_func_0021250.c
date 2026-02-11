authfree(VOID_A)
{
	int i;

	for (i = 0; i < maxauth; i++) urlfreehost(&(authlist[i].host));
	maxauth = 0;
}
