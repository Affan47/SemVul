showStats(g2sprop * prop) {
	g2sstats *stats = prop->stats;
	double ratio;
	if (prop->needsStats) {
		if (prop->parseTrk) {
			if (stats->trkunconverted != 0) {
				ratio = (double) stats->trkunconverted
						/ (stats->trkcount + stats->trkunconverted) * 100;
			} else {
				ratio = 0;
			}
			printf("Track Points:\n");
			printf("\ttrack count:\t%i\n", stats->trkcount);
			printf("\tpoint count:\t%i\n", stats->trkpoints);
			if (!prop->isFast) {
				printf("\ttotal length:\t%f\n", stats->trklength);
				printf("\tunconverted:\t%i(%5.2f%%)\n", stats->trkunconverted,
						ratio);
			}
		}
		if (prop->parseRte) {
			if (stats->rteunconverted != 0) {
				ratio = (double) stats->rteunconverted
						/ (stats->rtecount + stats->rteunconverted) * 100;
			} else {
				ratio = 0;
			}
			printf("Routes:\n");
			printf("\troute count:\t%i\n", stats->rtecount);
			printf("\tpoint count:\t%i\n", stats->rtepoints);
			if (!prop->isFast) {
				printf("\ttotal length:\t%f\n", stats->rtelength);
				printf("\tunconverted:\t%i(%5.2f%%)\n", stats->rteunconverted,
						ratio);
			}
		}
		if (prop->parseWpt) {
			printf("Waypoints:\n");
			printf("\tpoint count:\t%i\n", stats->wptpoints);
		}
	}
}
