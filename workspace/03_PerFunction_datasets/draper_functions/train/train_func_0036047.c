cdDiffMixed(cdCompTime ca, cdCompTime cb){

	static cdCompTime ZA = {1582, 10, 5, 0.0};
	static cdCompTime ZB = {1582, 10, 15, 0.0};
	double result;

	if (cdCompCompare(cb, ZB) == -1){
		if (cdCompCompare(ca, ZB) == -1) {
			result = cdDiffJulian(ca, cb);
		}
		else {
			result = cdDiffGregorian(ca, ZB) + cdDiffJulian(ZA, cb);
		}
	}
	else {
		if (cdCompCompare(ca, ZB) == -1){
			result = cdDiffJulian(ca, ZA) + cdDiffGregorian(ZB, cb);
		}
		else {
			result = cdDiffGregorian(ca, cb);
		}
	}
	return result;
}
