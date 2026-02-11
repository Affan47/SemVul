impulsesOrig(GLEDataSet* ds) {
	GLERange* range = ds->getDim(GLE_DIM_Y)->getRange();
	if (range->getMin() > 0.0) return range->getMin();
	if (range->getMax() < 0.0) return range->getMax();
	return 0.0;
}
