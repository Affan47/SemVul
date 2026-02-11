get_icaltimetype (icalproperty *prop,
                  struct icaltimetype (*get_prop_func) (const icalproperty *prop),
                                                        struct icaltimetype **t)
{
	if (!prop) {
		*t = NULL;
		return;
	}

	*t = g_new (struct icaltimetype, 1);
	**t = (* get_prop_func) (prop);
}
