bes_conn_try(const struct sess *sp, struct vbc *vc, const struct vdi_simple *vs)
{
	int s;
	struct backend *bp = vs->backend;
	char abuf1[VTCP_ADDRBUFSIZE];
	char pbuf1[VTCP_PORTBUFSIZE];

	CHECK_OBJ_NOTNULL(vs, VDI_SIMPLE_MAGIC);

	Lck_Lock(&bp->mtx);
	bp->refcount++;
	bp->n_conn++;
	Lck_Unlock(&bp->mtx);

	s = -1;
	assert(bp->ipv6 != NULL || bp->ipv4 != NULL);


	if (cache_param->prefer_ipv6 && bp->ipv6 != NULL) {
		s = vbe_TryConnect(sp, PF_INET6, bp->ipv6, bp->ipv6len, vs);
		vc->addr = bp->ipv6;
		vc->addrlen = bp->ipv6len;
	}
	if (s == -1 && bp->ipv4 != NULL) {
		s = vbe_TryConnect(sp, PF_INET, bp->ipv4, bp->ipv4len, vs);
		vc->addr = bp->ipv4;
		vc->addrlen = bp->ipv4len;
	}
	if (s == -1 && !cache_param->prefer_ipv6 && bp->ipv6 != NULL) {
		s = vbe_TryConnect(sp, PF_INET6, bp->ipv6, bp->ipv6len, vs);
		vc->addr = bp->ipv6;
		vc->addrlen = bp->ipv6len;
	}

	vc->fd = s;
	if (s < 0) {
		Lck_Lock(&bp->mtx);
		bp->n_conn--;
		bp->refcount--;
		Lck_Unlock(&bp->mtx);
		vc->addr = NULL;
		vc->addrlen = 0;
	} else {
		vc->vsl_id = s | VSL_BACKENDMARKER;
		VTCP_myname(s, abuf1, sizeof abuf1, pbuf1, sizeof pbuf1);
		WSL(sp->wrk, SLT_BackendOpen, vc->vsl_id, "%s %s %s ",
		    vs->backend->display_name, abuf1, pbuf1);
	}

}
