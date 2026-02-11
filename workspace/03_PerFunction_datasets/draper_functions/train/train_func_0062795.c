start_subtick(double dsubticks, double dticks, GLEAxis* ax) {
	double firstTick;
	if (ax->getNbPlaces() > 0) {
		firstTick = ax->getPlace(0);
	} else {
		GLERange range;
		range.copy(ax->getRange());
		roundrange(&range, false, false, dticks);
		firstTick = range.getMin();
	}
	if (firstTick <= ax->getMin()) {
		return firstTick;
	} else {
		double n = ceil((firstTick - ax->getMin()) / dsubticks) + 1;
		return firstTick - n * dsubticks;
	}
}
