LinesFormFromTextForm(const char *textForm) {

	std::vector<const char *> linesForm;
	int countQuotes = 0;
	int strings=1;
	int j=0;
	for (; countQuotes < (2*strings) && textForm[j] != '\0'; j++) {
		if (textForm[j] == '\"') {
			if (countQuotes == 0) {

				const char *line0 = textForm + j + 1;

				line0 = NextField(line0);

				strings += atoi(line0);
				line0 = NextField(line0);

				strings += atoi(line0);
			}
			if (countQuotes / 2 >= strings) {
				break;
			}
			if ((countQuotes & 1) == 0) {
				linesForm.push_back(textForm + j + 1);
			}
			countQuotes++;
		}
	}
	if (textForm[j] == '\0' || countQuotes / 2 > strings) {

		linesForm.clear();
	}
	return linesForm;
}
