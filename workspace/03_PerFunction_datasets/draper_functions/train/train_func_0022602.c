nodes_print(BIO *out, const char *name,
	STACK_OF(X509_POLICY_NODE) *nodes)
	{
	X509_POLICY_NODE *node;
	int i;
	BIO_printf(out, "%s Policies:", name);
	if (nodes)
		{
		BIO_puts(out, "\n");
		for (i = 0; i < sk_X509_POLICY_NODE_num(nodes); i++)
			{
			node = sk_X509_POLICY_NODE_value(nodes, i);
			X509_POLICY_NODE_print(out, node, 2);
			}
		}
	else
		BIO_puts(out, " <empty>\n");
	}
