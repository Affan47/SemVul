libipw_networks_allocate(struct libipw_device *ieee)
{
	int i, j;

	for (i = 0; i < MAX_NETWORK_COUNT; i++) {
		ieee->networks[i] = kzalloc(sizeof(struct libipw_network),
					    GFP_KERNEL);
		if (!ieee->networks[i]) {
			LIBIPW_ERROR("Out of memory allocating beacons\n");
			for (j = 0; j < i; j++)
				kfree(ieee->networks[j]);
			return -ENOMEM;
		}
	}

	return 0;
}
