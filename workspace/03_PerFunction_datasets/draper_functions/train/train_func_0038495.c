schi_dump(GF_Box *a, FILE * trace)
{
	GF_SchemeInformationBox *p;
	p = (GF_SchemeInformationBox *)a;
	fprintf(trace, "<SchemeInformationBox>\n");
	DumpBox(a, trace);
	if (p->ikms) gf_box_dump(p->ikms, trace);
	if (p->isfm) gf_box_dump(p->isfm, trace);
	if (p->okms) gf_box_dump(p->okms, trace);
	if (p->tenc) gf_box_dump(p->tenc, trace);
	gf_box_dump_done("SchemeInformationBox", a, trace);
	return GF_OK;
}
