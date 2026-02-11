upnp_service_gslist_find(GSList *services, enum upnp_service_type type)
{
	GSList *sl;

	GM_SLIST_FOREACH(services, sl) {
		upnp_service_t *usd = sl->data;

		upnp_service_check(usd);

		if (usd->type == type)
			return usd;
	}

	return NULL;
}
