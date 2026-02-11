dump_traces (TraceDesc *traces, const char *desc)
{
	int j;
	if (!show_traces)
		return;
	if (!traces->count)
		return;
	sort_context_array (traces);
	for (j = 0; j < traces->count; ++j) {
		int k;
		BackTrace *bt;
		bt = traces->traces [j].bt;
		if (!bt->count)
			continue;
		fprintf (outfile, "\t%llu %s from:\n", (unsigned long long) traces->traces [j].count, desc);
		for (k = 0; k < bt->count; ++k)
			fprintf (outfile, "\t\t%s\n", bt->methods [k]->name);
	}
}
