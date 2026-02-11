ReadTime(const char *prompt)
{
	string data;
	char *unprocessed = 0;
	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	tm.tm_isdst = -1;

	do {
		cout << prompt << ": ";
		getline(cin, data);
		unprocessed = strptime(data.c_str(), "%Y/%m/%d %H:%M", &tm);
	} while( !unprocessed );

	return Barry::TimeT(mktime(&tm));
}
