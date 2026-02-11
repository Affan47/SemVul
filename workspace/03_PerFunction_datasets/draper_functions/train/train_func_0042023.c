setminmax(double v, double *min, double *max) {
	if (v< *min) *min = v;
	if (v> *max) *max = v;
}
