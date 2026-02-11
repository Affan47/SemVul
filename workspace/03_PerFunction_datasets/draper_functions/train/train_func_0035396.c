mp4s_dump(GF_Box *a, FILE * trace)
{
	GF_MPEGSampleEntryBox *p;

	p = (GF_MPEGSampleEntryBox *)a;
	fprintf(trace, "<MPEGSystemsSampleDescriptionBox DataReferenceIndex=\"%d\">\n", p->dataReferenceIndex);
	DumpBox(a, trace);
	if (p->esd) {
		gf_box_dump(p->esd, trace);
	} else {
		fprintf(trace, "<!--INVALID MP4 FILE: ESDBox not present in MPEG Sample Description or corrupted-->\n");
	}
	if (a->type == GF_ISOM_BOX_TYPE_ENCS) {
		gf_box_array_dump(p->protections, trace);
	}
	gf_box_dump_done("MPEGSystemsSampleDescriptionBox", a, trace);
	return GF_OK;
}
