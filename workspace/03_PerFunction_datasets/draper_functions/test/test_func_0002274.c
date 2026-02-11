get_resultset_nodeset (GdaXsltIntCont * pdata, const char *resultset_name,
		       xmlXPathObjectPtr * nodeset, GError ** error)
{
	gpointer orig_key = NULL;
	gpointer value = NULL;
	GObject *result;
	int res;
#ifdef GDA_DEBUG_NO
	g_print ("searching resultset[%s]", resultset_name);
#endif

	if (g_hash_table_lookup_extended
	    (pdata->result_sets, resultset_name, &orig_key, &value)) {
#ifdef GDA_DEBUG_NO
		g_print ("resultset found [%p]\n", value);
#endif
		result = (GObject *) value;
	}
	else {
#ifdef GDA_DEBUG_NO
		g_print ("no resultset found\n");
#endif
		g_set_error (error, 0, 0,
			     "no resultset found for name [%s]\n",
			     resultset_name);
		*nodeset = NULL;
		return -1;
	}

	res = _utility_data_model_to_nodeset (GDA_DATA_MODEL (result),
					      nodeset, error);
	if (res < 0) {
#ifdef GDA_DEBUG_NO
		g_print ("_utility_data_model_to_nodeset fault");
#endif
		*nodeset = NULL;
		return -1;
	}
	return 0;
}
