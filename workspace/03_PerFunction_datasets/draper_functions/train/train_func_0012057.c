show_words()
{
	if (_nword > 0) {
		printf("DEBUG: ");
		for (unsigned int i = 0; i < _nword; i++) {
			printf("%d\"%s\" ", i, _word[i]);
		}
		printf("\n");
	} else {
		printf("DEBUG: commandline is blank\n");
	}

}
