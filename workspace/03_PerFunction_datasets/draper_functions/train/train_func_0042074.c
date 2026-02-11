addStrokeAdjustHint(int ctrl0, int ctrl1,
				     int firstPt, int lastPt) {
  if (hintsLength == hintsSize) {
    hintsSize = hintsLength ? 2 * hintsLength : 8;
    hints = (SplashPathHint *)greallocn(hints, hintsSize,
					sizeof(SplashPathHint));
  }
  hints[hintsLength].ctrl0 = ctrl0;
  hints[hintsLength].ctrl1 = ctrl1;
  hints[hintsLength].firstPt = firstPt;
  hints[hintsLength].lastPt = lastPt;
  ++hintsLength;
}
