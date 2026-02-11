dump_file_timestamps(GF_ISOFile *file, char *inName)
{
	u32 i, j, k, count;
	Bool has_error;
	FILE *dump;
	char szBuf[1024];

	if (inName) {
		strcpy(szBuf, inName);
		strcat(szBuf, "_ts.txt");
		dump = gf_f64_open(szBuf, "wt");
	} else {
		dump = stderr;
	}

	has_error = 0;
	for (i=0; i<gf_isom_get_track_count(file); i++) {
		u32 has_cts_offset = gf_isom_has_time_offset(file, i+1);

		fprintf(dump, "#dumping track ID %d timing: Num DTS CTS Size RAP\n", gf_isom_get_track_id(file, i+1));
		count = gf_isom_get_sample_count(file, i+1);

		for (j=0; j<count; j++) {
			u64 dts, cts;
			GF_ISOSample *samp = gf_isom_get_sample_info(file, i+1, j+1, NULL, NULL);
			dts = samp->DTS;
			cts = dts + (s32) samp->CTS_Offset;

			fprintf(dump, "Sample %d\tDTS "LLD"\tCTS "LLD"\t%d\t%d", j+1, LLD_CAST dts, LLD_CAST cts, samp->dataLength, samp->IsRAP);
			if (cts<dts) { fprintf(dump, " #NEGATIVE CTS OFFSET!!!"); has_error = 1;}

			gf_isom_sample_del(&samp);

			if (has_cts_offset) {
				for (k=0; k<count; k++) {
					u64 adts, acts;
					if (k==j) continue;
					samp = gf_isom_get_sample_info(file, i+1, k+1, NULL, NULL);
					adts = samp->DTS;
					acts = adts + (s32) samp->CTS_Offset;

					if (adts==dts) { fprintf(dump, " #SAME DTS USED!!!"); has_error = 1; }
					if (acts==cts) { fprintf(dump, " #SAME CTS USED!!! "); has_error = 1; }

					gf_isom_sample_del(&samp);
				}
			}

			fprintf(dump, "\n");
			gf_set_progress("Analysing Track Timing", j+1, count);
		}
		fprintf(dump, "\n\n");
		gf_set_progress("Analysing Track Timing", count, count);
	}
	if (inName) fclose(dump);
	if (has_error) fprintf(stderr, "\tFile has CTTS table errors\n");
}
