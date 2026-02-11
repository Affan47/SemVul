trun_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_TrunEntry *ent;
	GF_TrackFragmentRunBox *p;

	p = (GF_TrackFragmentRunBox *)a;
	fprintf(trace, "<TrackRunBox SampleCount=\"%d\"", p->sample_count);

	if (p->flags & GF_ISOM_TRUN_DATA_OFFSET)
		fprintf(trace, " DataOffset=\"%d\"", p->data_offset);
	fprintf(trace, ">\n");

	if (p->flags & GF_ISOM_TRUN_FIRST_FLAG) {
		sample_flags_dump("FirstSampleFlags", p->first_sample_flags, trace);
	}
	DumpBox(a, trace);
	gf_full_box_dump(a, trace);

	if (p->flags & (GF_ISOM_TRUN_DURATION|GF_ISOM_TRUN_SIZE|GF_ISOM_TRUN_CTS_OFFSET|GF_ISOM_TRUN_FLAGS)) {
		i=0;
		while ((ent = (GF_TrunEntry *)gf_list_enum(p->entries, &i))) {

			fprintf(trace, "<TrackRunEntry");

			if (p->flags & GF_ISOM_TRUN_DURATION)
				fprintf(trace, " Duration=\"%d\"", ent->Duration);
			if (p->flags & GF_ISOM_TRUN_SIZE)
				fprintf(trace, " Size=\"%d\"", ent->size);
			if (p->flags & GF_ISOM_TRUN_CTS_OFFSET)
				fprintf(trace, " CTSOffset=\"%d\"", ent->CTS_Offset);

			if (p->flags & GF_ISOM_TRUN_FLAGS) {
				fprintf(trace, " SamplePadding=\"%d\" Sync=\"%d\" DegradationPriority=\"%d\"",
					GF_ISOM_GET_FRAG_PAD(ent->flags), GF_ISOM_GET_FRAG_SYNC(ent->flags), GF_ISOM_GET_FRAG_DEG(ent->flags));
			}
			fprintf(trace, "/>\n");
		}
	} else {
		fprintf(trace, "<!-- all default values used -->\n");
	}
	gf_box_dump_done("TrackRunBox", a, trace);
	return GF_OK;
}
