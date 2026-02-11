e_vcard_attribute_remove_params (EVCardAttribute *attr)
{
	g_return_if_fail (attr != NULL);

	g_list_foreach (attr->params, (GFunc) e_vcard_attribute_param_free, NULL);
	g_list_free (attr->params);
	attr->params = NULL;


	attr->encoding_set = FALSE;
	attr->encoding = EVC_ENCODING_RAW;
}
