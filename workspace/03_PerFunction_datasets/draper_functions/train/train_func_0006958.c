zSetVerbosityLevel(int verbosity) {

  if(LIBVERBOSITY == NULL) {
	LIBVERBOSITY = zMalloc(sizeof(zVerbosityObject), "zSetVerbosityLevel");
	LIBVERBOSITY->verbosity_level = verbosity;
	zInitTVec(&LIBVERBOSITY->features, 10);

  }
  else {
	LIBVERBOSITY->verbosity_level = verbosity;
  }
}
