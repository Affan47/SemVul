contains(const char *testVar) const {
		return (var && (0 == strcmp(var, testVar)))
			|| (link && link->contains(testVar));
	}
