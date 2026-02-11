handleDeleteCommand(bool calledFromBreakpoint, int line, int fileNumber) {
	char *parameter = strtok(NULL, "");
	if (parameter == NULL) {
		if (calledFromBreakpoint)
			deleteBreakpoint(line, fileNumber);
		else
			printf("No current breakpoint to delete\n");
	} else
		deleteBreakpoint(atoi(parameter), fileNumber);
}
