gsf_output_proxy_create (GsfOutput *wrapped, char const *uri, GError **err)
{
	if (!wrapped) {
		g_set_error (err, gsf_output_error_id (), 0,
			     "Unable to write to %s", uri);
		return NULL;
	}


	return gsf_output_proxy_new (wrapped);
}
