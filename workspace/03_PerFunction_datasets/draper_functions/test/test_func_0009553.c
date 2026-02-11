X509_POLICY_NODE_print(BIO *out, X509_POLICY_NODE *node, int indent)
	{
	const X509_POLICY_DATA *dat = node->data;

	BIO_printf(out, "%*sPolicy: ", indent, "");

	i2a_ASN1_OBJECT(out, dat->valid_policy);
	BIO_puts(out, "\n");
	BIO_printf(out, "%*s%s\n", indent + 2, "",
		node_data_critical(dat) ? "Critical" : "Non Critical");
	if (dat->qualifier_set)
		print_qualifiers(out, dat->qualifier_set, indent + 2);
	else
		BIO_printf(out, "%*sNo Qualifiers\n", indent + 2, "");
	}
