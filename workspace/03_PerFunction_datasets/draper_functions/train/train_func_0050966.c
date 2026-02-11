_ping_slurmctld(char *control_machine, char *backup_controller)
{
	static char *state[2] = { "UP", "DOWN" };
	int primary = 1, secondary = 1;
	int down_msg = 0;

	if (slurm_ping(1) == SLURM_SUCCESS)
		primary = 0;
	if (slurm_ping(2) == SLURM_SUCCESS)
		secondary = 0;
	fprintf(stdout, "Slurmctld(primary/backup) ");
	if (control_machine || backup_controller) {
		fprintf(stdout, "at ");
		if (control_machine) {
			fprintf(stdout, "%s/", control_machine);
			if (primary)
				down_msg = 1;
		} else
			fprintf(stdout, "(NULL)/");
		if (backup_controller) {
			fprintf(stdout, "%s ", backup_controller);
			if (secondary)
				down_msg = 1;
		} else
			fprintf(stdout, "(NULL) ");
	}
	fprintf(stdout, "are %s/%s\n",
		state[primary], state[secondary]);

	if (down_msg && (getuid() == 0)) {
		fprintf(stdout, "*****************************************\n");
		fprintf(stdout, "** RESTORE SLURMCTLD DAEMON TO SERVICE **\n");
		fprintf(stdout, "*****************************************\n");
	}
}
