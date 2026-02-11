hmap_nextNN(CTX ctx, kmapptr_t *m, knitr_t *mitr, ksfp_t *rsfp)
{
	knh_hmap_t *hmap = (knh_hmap_t*)m;
	size_t i;
	for(i = mitr->index; i < hmap->arenasize; i++) {
		knh_hentry_t *e = hmap->arena + i;
		if(e->hcode == ((khashcode_t)-1) && e->nvalue == 0) continue;
		rsfp[0].ndata = e->nkey;
		rsfp[1].ndata = e->nvalue;
		mitr->index = i + 1;
		return 1;
	}
	mitr->index = hmap->arenasize;
	return 0;
}
