lsr1_dump(GF_Box *a, FILE * trace)
{
	GF_LASeRSampleEntryBox *p = (GF_LASeRSampleEntryBox*)a;
	fprintf(trace, "<LASeRSampleEntryBox DataReferenceIndex=\"%d\">\n", p->dataReferenceIndex);
	DumpBox(a, trace);
	if (p->lsr_config) gf_box_dump(p->lsr_config, trace);
	if (p->bitrate) gf_box_dump(p->bitrate, trace);
	if (p->descr) gf_box_dump(p->descr, trace);
	gf_box_dump_done("LASeRSampleEntryBox", a, trace);
	return GF_OK;
}
