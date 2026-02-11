uuid_is_nil(uuid_t *uuid)
{
	int	i;
	char	*cp = (char *)uuid;

	if (uuid == NULL)
		return 0;

	for (i = 0; i < sizeof *uuid; i++)
		if (*cp++) return 0;
	return 1;
}
