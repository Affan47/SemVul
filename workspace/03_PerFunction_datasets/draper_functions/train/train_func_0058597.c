endProgram() {
	return frozen_ || (prepareProgram() && transformProgram(!eqOpts_.noSCC));
}
