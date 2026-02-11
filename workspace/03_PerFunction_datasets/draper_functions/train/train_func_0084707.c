MouseLeave() {
	SetHotSpotRange(NULL);
	if (!HaveMouseCapture()) {
		ptMouseLast = Point(-1,-1);
		DwellEnd(true);
	}
}
