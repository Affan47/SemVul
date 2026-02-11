_getopt_ext_tailit(int argc,
					   char **argv,
					   int hasArg,
					   int recognized)
{
	char *_optPtr=NULL;
	char *_optArgPtr=NULL;
	int _endIndex=optind_last;
	int _nextDest=optind_ext;
	int _nextSource=optind_ext;

	_optPtr = argv[optind_ext];
	if(hasArg) {
		_nextSource = optind_ext + 2;
		_endIndex = ((recognized)?_optind_firstRecognized:_optind_firstHandled);
		_optArgPtr = argv[optind_ext + 1];
	} else {
		_nextSource = optind_ext + 1;
		_endIndex =  ((recognized)?_optind_firstRecognized:_optind_firstHandled);
		_optArgPtr = NULL;
	}

	while(_nextSource < _endIndex) {
		argv[_nextDest] = argv[_nextSource];
		_nextSource++;
		_nextDest++;
	}

	argv[_nextDest] = _optPtr;

	if(hasArg) {
		argv[_nextDest + 1] = _optArgPtr;
		if(recognized) {
			_optind_firstRecognized -=2;
		}
		_optind_firstHandled -=2;
	} else {
		if(recognized) {
			_optind_firstRecognized -=1;
		}
		_optind_firstHandled -=1;
	}
	optind_last = _optind_firstRecognized;
	return(0);
}
