draw_err(GLEDataSet* dataSet, const string& errdescr, bool isUp, bool isHoriz, double errwd, const char* descr) {
	dataSet->checkRanges();
	if (errwd == 0) {
		double hei;
		g_get_hei(&hei);
		errwd = hei/3;
	}
	int errID;
	double value;
	bool enable, percentage;
	setupdown(errdescr, &enable, &errID, &percentage, &value);
	g_set_color(dataSet->color);
	g_set_line_width(dataSet->lwidth);
	GLEDataPairs pairs(dataSet);
	GLEDataPairs errPairs;
	if (errID != 0) {
		GLEDataSet* errDataset = getDataset(errID, descr);
		errPairs.copyDimension(errDataset, 1);
		errDataset->validateNbPoints(dataSet->np, descr);
	}
	vector<double>* errDimension = pairs.getDimension(isHoriz ? 0 : 1);
	for (unsigned int i = 0; i < dataSet->np; i++) {
		int miss = false;
		double error = 0.0;
		if (errID != 0) {
			miss = errPairs.getM(i);
			error = errPairs.getY(i);
		} else {
			error = value;
			if (percentage) error *= fabs(errDimension->at(i)) / 100.0;
		}
		if (enable && !pairs.getM(i) && !miss) {
			if (!isUp) {
				error = error * -1;
			}
			if (isHoriz) {
				draw_herrbar(pairs.getX(i), pairs.getY(i), error, errwd, dataSet);
			} else {
				draw_errbar(pairs.getX(i), pairs.getY(i), error, errwd, dataSet);
			}
		}
	}
}
