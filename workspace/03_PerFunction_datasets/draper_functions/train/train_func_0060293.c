checkPICSagainstoption(String s, const char *l, int opt, std::string m)
{
	if (s.indexOf(l) != -1) {

		int i = 0;

		s = s.after(l);
		if (s.indexOf(" ") != -1) {

			s = s.before(" ");
		}

		if (s.length() > 0) {
			i = s.toInteger();
			if (opt < i) {
				isItNaughty = true;
				whatIsNaughty = m + " ";
				whatIsNaughty += o.language_list.getTranslation(1000);

				whatIsNaughtyCategories = "PICS";
				whatIsNaughtyLog = whatIsNaughty;
			}
		}
	}
}
