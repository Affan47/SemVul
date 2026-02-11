convert_string_to_mac(const char* string, unsigned char* mac)
{
	int c;
	for(c = 0; c < 6 && string; c++) {
		int x = 0;
		if (string)
			sscanf(string, "%x", &x);
		mac[c] = x;
		string = strchr(string, ':');
		if (string)
			string++;
	}
}
