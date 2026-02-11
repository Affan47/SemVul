endpoint_init_a2dp_source(struct media_endpoint *endpoint,
						gboolean delay_reporting,
						int *err)
{
	endpoint->sep = a2dp_add_sep(&endpoint->adapter->src,
					AVDTP_SEP_TYPE_SOURCE, endpoint->codec,
					delay_reporting, &a2dp_endpoint,
					endpoint, a2dp_destroy_endpoint, err);
	if (endpoint->sep == NULL)
		return FALSE;

	return TRUE;
}
