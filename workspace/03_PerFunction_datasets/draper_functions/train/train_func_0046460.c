main (int argc, char * argv[]) {


	FILE *file;
	if (argc == 1 || argc > 2) {
		REPORT("Wrong input params.")
		HALT(INTERNAL_ERROR)
	}
	if ((file = fopen(argv[1],"r")) == NULL) {
		REPORT("File opening error.")
		HALT(INTERNAL_ERROR)
	}
	delegateSourceFile(file);


	typeList instructionList;
	listInit(&instructionList);


	int statusCode;


	statusCode = parseStarter(&instructionList);

	switch (statusCode) {
		case SUCCESS:
			break;

		default:
			switch (statusCode) {
				case LEXICAL_ERROR:
					fprintf(stderr,"Lexical analysis failure.\n");
					fprintf(stderr,"Incident caused at %i:%i.\n",
						troubleLine, troubleColumn);
					break;

				case PARSER_ERROR:
					fprintf(stderr,"Syntax analysis failure.\n");
					break;

				case INTERNAL_ERROR:
					fprintf(stderr,"Internal interpreter error.\n");
					break;

				case S_FUNC_ERROR:
					fprintf(stderr,
						"Semantic error: undef/redef of the function.\n");
					break;

				case S_PARAM_ERROR:
					fprintf(stderr,"Semantic error: function call params.\n");
					break;

				case S_DECLAR_ERROR:
					fprintf(stderr,"Semantic error: undeclared variable.\n");
					break;
			}
			CLOSE_ALL
			HALT(statusCode)
			break;
	}


	statusCode = interpreterStart(&instructionList);

	switch (statusCode) {
		case SUCCESS:
			break;

		default:
			switch (statusCode) {
				case INTERNAL_ERROR:
					fprintf(stderr,"Internal interpreter error.\n");
					break;

				case S_EXPRESS_ERROR:
					fprintf(stderr,
						"Semantic error: operation comptability.\n");
					break;

				case S_ZERODIV_ERROR:
					fprintf(stderr,"Semantic error: divide by zero.\n");
					break;

				case S_TYPE_ERROR:
					fprintf(stderr,"Semantic error: type conversion error.\n");
					break;

				case S_OTHER_ERROR:
					fprintf(stderr,"Semantic error: other error.\n");
					break;
			}
			CLOSE_ALL
			HALT(statusCode)
			break;
	}


	CLOSE_ALL
	HALT(statusCode)

}
