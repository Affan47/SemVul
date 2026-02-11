meta_dump(GF_Box *a, FILE * trace)
{
	GF_MetaBox *p;
	p = (GF_MetaBox *)a;
	fprintf(trace, "<MetaBox>\n");
	DumpBox(a, trace);
	gf_full_box_dump(a, trace);

	if (p->handler) gf_box_dump(p->handler, trace);
	if (p->primary_resource) gf_box_dump(p->primary_resource, trace);
	if (p->file_locations) gf_box_dump(p->file_locations, trace);
	if (p->item_locations) gf_box_dump(p->item_locations, trace);
	if (p->protections) gf_box_dump(p->protections, trace);
	if (p->item_infos) gf_box_dump(p->item_infos, trace);
	if (p->IPMP_control) gf_box_dump(p->IPMP_control, trace);
	gf_box_dump_done("MetaBox", a, trace);
	return GF_OK;
}
