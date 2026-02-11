VSetVisibility(double d)
{
	int       i;
	double    k;

	_VDefaultWorkContext->visibility = d;
	if (_VDefaultWorkContext->visTable) {
		free((char *) _VDefaultWorkContext->visTable);
	}

	_VDefaultWorkContext->visTable = (double *) Vmalloc(sizeof(double) *
									_VDefaultWorkContext->depthCueSteps);

	k = log(1.0 / (double) _VDefaultWorkContext->depthCueSteps) /
		_VDefaultWorkContext->visibility;

#ifdef DEBUG
	fprintf(stderr, "k = %lg\n", k);
#endif

	for (i = 0; i < _VDefaultWorkContext->depthCueSteps - 1; ++i) {
		_VDefaultWorkContext->visTable[i] =
			log(1.0 - (double) (i + 1) /
				(double) _VDefaultWorkContext->depthCueSteps) / k;
#ifdef DEBUG
		fprintf(stderr, "next threshold is %lg units\n",
				_VDefaultWorkContext->visTable[i]);
#endif
	}
}
