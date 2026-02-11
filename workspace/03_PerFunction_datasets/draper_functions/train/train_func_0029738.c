strip_command(char *line) {
	int start,end;
	static char *command=NULL;
	static int length=0;

	for (start=0;line[start] && isspace(line[start]);start++) ;
	if (!line[start]) return NULL;

	for (end=start+1;line[end] && !isspace(line[end]);end++) ;

	if (end-start+1 > length) {
		if (command) free(command);
		length = end-start+1;
		command=malloc(length);
	}
	strncpy(command,line+start,end-start);
	command[end-start]=0;
	return command;
}
