Socket_getSoTimeout(CTX ctx, ksfp_t *sfp _RIX)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	struct timeval ret = {0, 0};
	unsigned int len = sizeof(ret);
	if(getsockopt(so->sd, SOL_SOCKET, SO_SNDTIMEO, &ret, &len) == -1) {
		KNH_NTRACE2(ctx, "getsockopt", K_PERROR, KNH_LDATA(LOG_i("sd", so->sd), LOG_i("port", so->port)));
		ret.tv_sec = 0;
	} else {
		KNH_NTRACE2(ctx, "getsockopt", K_OK, KNH_LDATA(LOG_i("sd", so->sd), LOG_i("port", so->port)));
	}
	RETURNi_(ret.tv_sec * 1000 + ret.tv_sec / 1000);
}
