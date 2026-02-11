mlx4_ib_guid_port_init(struct mlx4_ib_dev *dev, int port)
{
	int j, k, entry;
	__be64 guid;


	for (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) {
		for (k = 0; k < NUM_ALIAS_GUID_IN_REC; k++) {
			entry = j * NUM_ALIAS_GUID_IN_REC + k;

			if (!entry || entry > dev->dev->persist->num_vfs ||
			    !mlx4_is_slave_active(dev->dev, entry))
				continue;
			guid = mlx4_get_admin_guid(dev->dev, entry, port);
			*(__be64 *)&dev->sriov.alias_guid.ports_guid[port - 1].
				all_rec_per_port[j].all_recs
				[GUID_REC_SIZE * k] = guid;
			pr_debug("guid was set, entry=%d, val=0x%llx, port=%d\n",
				 entry,
				 be64_to_cpu(guid),
				 port);
		}
	}
}
