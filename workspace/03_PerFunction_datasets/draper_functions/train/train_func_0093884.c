gar_read_cp(struct gar_graph *graph, u_int32_t offset)
{
	struct gimg *gimg = graph->sub->gimg;
	struct cpoint *p;
	struct central_point n;
	int rc;
	unsigned i;

	glseek(gimg, offset, SEEK_SET);
	rc = gread(gimg, &n, sizeof(struct central_point));
	if (rc != sizeof(struct nod_node)) {
		log(1, "NOD: Error reading cpoint\n");
		return NULL;
	}
	p = gar_alloc_cp();
	if (!p)
		return NULL;
	if (n.croads) {
		i = n.croads*graph->sub->net->nod->roadptrsize;
		p->roads = malloc(i);
		if (!p->roads)
			goto out_err;
		p->rpsize = graph->sub->net->nod->roadptrsize;
		p->croads = n.croads;
		rc = gread(gimg, p->roads,i);
		if (rc != i)
			goto out_err;
		i = (n.cidxs) * 3;
		p->cidxs = n.cidxs;
		p->idx = malloc(i);
		if (!p->idx)
			goto out_err;
		rc = gread(gimg, p->idx,i);
		if (rc != i)
			goto out_err;
	}
	p->crestr = n.crestr;
	if (p->crestr) {
		p->restr = malloc(p->crestr);
		if (!p->restr)
			goto out_err;
		rc = gread(gimg, p->restr,p->crestr);
		if (rc != p->crestr)
			goto out_err;
	}
	p->lng = *(u_int32_t *) n.lng & 0xffffff;
	p->lat = *(u_int32_t *) n.lat & 0xffffff;
	p->offset = offset;
	log(11, "CPNT: %d at %f/%f\n", p->offset, GARDEG(p->lng), GARDEG(p->lat));
	return p;
out_err:
	gar_free_cpoint(p);
	return NULL;
}
