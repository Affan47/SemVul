drawErrorBars(int dn) {
	GLEDataSet* dataSet = dp[dn];
	if (dataSet->errup.size() != 0) {
		draw_err(dataSet, dataSet->errup, true, false, dataSet->errwidth, "error up");
	}
	if (dataSet->errdown.size() != 0) {
		draw_err(dataSet, dataSet->errdown, false, false, dataSet->errwidth, "error down");
	}
	if (dataSet->herrup.size() != 0) {
		draw_err(dataSet, dataSet->herrup, true, true, dataSet->herrwidth, "error right");
	}
	if (dataSet->herrdown.size() != 0) {
		draw_err(dataSet, dataSet->herrdown, false, true, dataSet->herrwidth, "error left");
	}
}
