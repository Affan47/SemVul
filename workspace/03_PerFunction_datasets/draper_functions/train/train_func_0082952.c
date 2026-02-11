allocate_method_table(struct ib_mad_mgmt_method_table **method)
{

	*method = kzalloc(sizeof **method, GFP_ATOMIC);
	if (!*method) {
		pr_err("No memory for ib_mad_mgmt_method_table\n");
		return -ENOMEM;
	}

	return 0;
}
