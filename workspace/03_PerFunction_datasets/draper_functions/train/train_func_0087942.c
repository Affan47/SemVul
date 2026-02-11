xlhdxload(XLabels_t * xlp)
{
    int i;
    int order = xlhorder(xlp);

    for (i = 0; i < xlp->n_objs; i++) {
	HDict_t *hp;
	point pi;

	hp = NEW(HDict_t);

	hp->d.data = &xlp->objs[i];
	hp->d.rect = objplpmks(xlp, &xlp->objs[i]);

	pi.x = hp->d.rect.boundary[0] +
	    (hp->d.rect.boundary[2] - hp->d.rect.boundary[0]) / 2;
	pi.y = hp->d.rect.boundary[1] +
	    (hp->d.rect.boundary[3] - hp->d.rect.boundary[1]) / 2;

	hp->key = hd_hil_s_from_xy(pi, order);

#if 0
	if (dtsearch(xlp->hdx, hp) != 0) {
	    free(hp);
	    continue;
	}
#endif
	if (!(dtinsert(xlp->hdx, hp)))
	    return -1;
    }
    return 0;
}
