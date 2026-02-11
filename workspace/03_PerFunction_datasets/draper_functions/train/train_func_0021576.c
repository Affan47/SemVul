hmap_removeNN(CTX ctx, kmapptr_t* m, ksfp_t *ksfp)
{
	knh_hmap_t *hmap = (knh_hmap_t*)m;
	khashcode_t hcode = (khashcode_t)ksfp[0].ndata;
	knh_hentry_t *e = hmap_getentry(hmap, hcode);
	while(e != NULL) {
		if(e->hcode == hcode) {
			hmap_remove(hmap, e);
			hmap_unuse(hmap, e);
			return;
		}
		e = e->next;
	}
}
