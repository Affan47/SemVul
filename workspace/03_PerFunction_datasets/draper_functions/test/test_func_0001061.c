handle_info(user_t *u)
{
	unsigned int i;

	if (u == NULL)
		return;
	if (floodcheck(u, NULL))
		return;

	for (i = 0; infotext[i]; i++)
		numeric_sts(me.me, 371, u, ":%s", infotext[i]);

	numeric_sts(me.me, 374, u, ":End of /INFO list");
}
