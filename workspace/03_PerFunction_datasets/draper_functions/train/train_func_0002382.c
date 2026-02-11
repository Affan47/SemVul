hpsa_alloc_sas_node(struct device *parent_dev)
{
	struct hpsa_sas_node *hpsa_sas_node;

	hpsa_sas_node = kzalloc(sizeof(*hpsa_sas_node), GFP_KERNEL);
	if (hpsa_sas_node) {
		hpsa_sas_node->parent_dev = parent_dev;
		INIT_LIST_HEAD(&hpsa_sas_node->port_list_head);
	}

	return hpsa_sas_node;
}
