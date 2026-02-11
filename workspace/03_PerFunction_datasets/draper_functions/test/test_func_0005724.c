SubstituteByPosition(Document *doc, const char *text, int *length) {
	substituted.clear();
	DocumentIndexer di(doc, doc->Length());
	search.GrabMatches(di);
	for (int j = 0; j < *length; j++) {
		if (text[j] == '\\') {
			if (text[j + 1] >= '0' && text[j + 1] <= '9') {
				unsigned int patNum = text[j + 1] - '0';
				unsigned int len = search.eopat[patNum] - search.bopat[patNum];
				if (!search.pat[patNum].empty())
					substituted.append(search.pat[patNum].c_str(), len);
				j++;
			} else {
				j++;
				switch (text[j]) {
				case 'a':
					substituted.push_back('\a');
					break;
				case 'b':
					substituted.push_back('\b');
					break;
				case 'f':
					substituted.push_back('\f');
					break;
				case 'n':
					substituted.push_back('\n');
					break;
				case 'r':
					substituted.push_back('\r');
					break;
				case 't':
					substituted.push_back('\t');
					break;
				case 'v':
					substituted.push_back('\v');
					break;
				case '\\':
					substituted.push_back('\\');
					break;
				default:
					substituted.push_back('\\');
					j--;
				}
			}
		} else {
			substituted.push_back(text[j]);
		}
	}
	*length = static_cast<int>(substituted.length());
	return substituted.c_str();
}
