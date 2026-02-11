pcie_ecrc_get_policy(char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ecrc_policy_str); i++)
		if (!strncmp(str, ecrc_policy_str[i],
			     strlen(ecrc_policy_str[i])))
			break;
	if (i >= ARRAY_SIZE(ecrc_policy_str))
		return;

	ecrc_policy = i;
}
