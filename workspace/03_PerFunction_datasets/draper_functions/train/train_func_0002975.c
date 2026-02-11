gretl_bundle_print (gretl_bundle *bundle, PRN *prn)
{
    if (bundle == NULL) {
	return E_DATA;
    } else {
	user_var *u = get_user_var_by_data(bundle);
	const char *name = user_var_get_name(u);
	int n_items = g_hash_table_size(bundle->ht);

	if (n_items == 0) {
	    pprintf(prn, "bundle %s: empty\n", name);
	} else {
	    if (bundle->creator != NULL) {
		pprintf(prn, "bundle %s, created by %s:\n",
			name, bundle->creator);
	    } else {
		pprintf(prn, "bundle %s:\n", name);
	    }
	    g_hash_table_foreach(bundle->ht, print_bundled_item, prn);
	    pputc(prn, '\n');
	}
	return 0;
    }
}
