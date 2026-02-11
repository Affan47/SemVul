del_ca(SCA *c)
{
	int i, j, k, eq, mask = 1;
	adapter *ad;
	mutex_lock(&ca_mutex);

	for (i = 0; i < MAX_CA; i++)
	{
		if (ca[i].enabled)
		{
			eq = 1;
			for (j = 0; j < sizeof(ca[0].action) / sizeof(ca_action); j++)
				if (ca[i].action[j] != c->action[j])
					eq = 0;
			if (eq)
			{
				ca[i].enabled = 0;
				for (k = 0; k < MAX_ADAPTERS; k++)
				{
					if ((ad = get_adapter_nw(k)))
						ad->ca_mask &= ~mask;
				}
			}
		}
		mask = mask << 1;
	}
	i = MAX_CA;
	while (--i >= 0 && !ca[i].enabled)
		;
	nca = i + 1;


	mutex_unlock(&ca_mutex);
}
