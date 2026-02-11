addcommand(struct command *c) {
	if(!roomcmds) {
		struct command *ca = malloc((numcmds * 2) * sizeof *commands);
		memcpy(ca, commands, numcmds * sizeof *commands);
		if(commands != _commands)
			free(commands);

		commands = ca;
		roomcmds = numcmds;
	}

	commands[numcmds] = *c;
	numcmds++;
	roomcmds--;
	cmdrefresh();
}
