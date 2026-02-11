checkPath(parsedata * pdata) {
	pathattr *pattr = pdata->pattr;
	g2sprop *prop = pdata->prop;

	if (pattr->count < prop->minpoints) {
		fprintf(stderr,
				"gpx2shp:%s:%i track was not converted because of less then %d points. \n",
				prop->sourcefile, (int)XML_GetCurrentLineNumber(pdata->parser),
				prop->minpoints);
		countUnconverted(pdata);
		return 0;

	} else if (pattr->length < prop->minlength * prop->length2meter) {
		fprintf(stderr,
				"gpx2shp:%s:%i track was not converted because it is shorter than %dm.\n",
				prop->sourcefile, (int)XML_GetCurrentLineNumber(pdata->parser),
				prop->minlength);
		countUnconverted(pdata);
		return 0;

	} else if (pattr->interval < prop->mintime * prop->time2sec) {
		fprintf(stderr,
				"gpx2shp:%s:%i track was not converted because it is shorter than %d sed.\n",
				prop->sourcefile, (int)XML_GetCurrentLineNumber(pdata->parser),
				prop->mintime);
		countUnconverted(pdata);
		return 0;

	} else if (0 && pattr->speed == .0) {
		fprintf(stderr,
				"gpx2shp:%s:%i track was not converted because no move recorded.\n",
				prop->sourcefile, (int)XML_GetCurrentLineNumber(pdata->parser));
		countUnconverted(pdata);
		return 0;
	}
	return 1;
}
