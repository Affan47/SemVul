Idle() {

	bool idleDone;

	bool wrappingDone = !Wrapping();

	if (!wrappingDone) {

		WrapLines(wsIdle);

		if (!wrapPending.NeedsWrap())
			wrappingDone = true;
	}


	idleDone = wrappingDone;

	return !idleDone;
}
