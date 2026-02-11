get_mci_for_node_id(u8 node_id)
{
	struct sbridge_dev *sbridge_dev;

	list_for_each_entry(sbridge_dev, &sbridge_edac_list, list) {
		if (sbridge_dev->node_id == node_id)
			return sbridge_dev->mci;
	}
	return NULL;
}
