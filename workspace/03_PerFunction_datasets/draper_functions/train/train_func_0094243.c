setPositionIncrement(int32_t posIncr) {
	if (posIncr < 0) {
		_CLTHROWA(CL_ERR_IllegalArgument,"positionIncrement must be >= 0");
	}
	positionIncrement = posIncr;
}
