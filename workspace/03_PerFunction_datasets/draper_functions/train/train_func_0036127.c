getPortOption (int argc, char *argv[], const std::string& option, int defaultValue)
{
	for (int i=0; i < argc-1; i++) {
		if (option == argv[i]) {
			int val = strtol( argv[i+1], 0, 10);
			if (val) return val;
		}
	}
	return defaultValue;
}
