printHelp(const OptionContext& root) {
	printf("%s version %s\n", getName(), getVersion());
	printUsage();
	ProgramOptions::FileOut out(stdout);
	root.description(out);
	printf("\n");
	printUsage();
	printf("Default command-line:\n%s %s\n", getName(), root.defaults(strlen(getName())+1).c_str());
	fflush(stdout);
}
