ServerSocket_getLocalPort(CTX ctx, ksfp_t *sfp _RIX)
{
	knh_serversocket_t *ss = (knh_serversocket_t *)((sfp[0].p)->rawptr);
	RETURNi_(ss->port);
}
