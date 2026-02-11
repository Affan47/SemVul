SPF_dns_resolv_new(SPF_dns_server_t *layer_below,
				const char *name, int debug)
{
	SPF_dns_server_t		*spf_dns_server;

#if HAVE_DECL_RES_NINIT
	pthread_once(&res_state_control, SPF_dns_resolv_init_key);
#else
	if (res_init() != 0) {
		SPF_warning("Failed to call res_init()");
		return NULL;
	}
#endif

	spf_dns_server = malloc(sizeof(SPF_dns_server_t));
	if (spf_dns_server == NULL)
		return NULL;
	memset(spf_dns_server, 0, sizeof(SPF_dns_server_t));

	if (name ==  NULL)
		name = "resolv";

	spf_dns_server->destroy     = SPF_dns_resolv_free;
	spf_dns_server->lookup      = SPF_dns_resolv_lookup;
	spf_dns_server->get_spf     = NULL;
	spf_dns_server->get_exp     = NULL;
	spf_dns_server->add_cache   = NULL;
	spf_dns_server->layer_below = layer_below;
	spf_dns_server->name        = name;
	spf_dns_server->debug       = debug;

	return spf_dns_server;
}
