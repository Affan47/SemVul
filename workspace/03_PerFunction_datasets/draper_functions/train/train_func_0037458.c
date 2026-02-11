SetTopLine(int topLineNew) {
	if (topLine != topLineNew) {
		topLine = topLineNew;
		ContainerNeedsUpdate(SC_UPDATE_V_SCROLL);
	}
	posTopLine = pdoc->LineStart(cs.DocFromDisplay(topLine));
}
