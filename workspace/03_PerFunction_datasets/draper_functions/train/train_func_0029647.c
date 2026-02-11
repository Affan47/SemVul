X509_policy_check(X509_POLICY_TREE **ptree, int *pexplicit_policy,
			STACK_OF(X509) *certs,
			STACK_OF(ASN1_OBJECT) *policy_oids,
			unsigned int flags)
	{
	int ret;
	X509_POLICY_TREE *tree = NULL;
	STACK_OF(X509_POLICY_NODE) *nodes, *auth_nodes = NULL;
	*ptree = NULL;

	*pexplicit_policy = 0;
	ret = tree_init(&tree, certs, flags);

	switch (ret)
		{


		case 2:
		return 1;


		case -1:
		return -1;


		case 0:
		return 0;


		case 6:
		*pexplicit_policy = 1;
		return -2;


		case 5:
		*pexplicit_policy = 1;
		break;


		case 1:
		if (!tree)


			return 1;
		break;
		}

	if (!tree) goto error;
	ret = tree_evaluate(tree);

	tree_print("tree_evaluate()", tree, NULL);

	if (ret <= 0)
		goto error;


	if (ret == 2)
		{
		X509_policy_tree_free(tree);
		if (*pexplicit_policy)
			return -2;
		else
			return 1;
		}


	ret = tree_calculate_authority_set(tree, &auth_nodes);

	if (!ret)
		goto error;

	if (!tree_calculate_user_set(tree, policy_oids, auth_nodes))
		goto error;

	if (ret == 2)
		sk_X509_POLICY_NODE_free(auth_nodes);

	if (tree)
		*ptree = tree;

	if (*pexplicit_policy)
		{
		nodes = X509_policy_tree_get0_user_policies(tree);
		if (sk_X509_POLICY_NODE_num(nodes) <= 0)
			return -2;
		}

	return 1;

	error:

	X509_policy_tree_free(tree);

	return 0;

	}
