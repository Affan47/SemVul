Cmd_Blox_f(edict_t * ent)
{
	char *cmd = gi.args();
	float ftmp;

	if(cmd == NULL || strlen(cmd) == 0) {
		gi.cprintf(ent, PRINT_HIGH, "Blox command help:\n");
		gi.cprintf(ent, PRINT_HIGH, " blox create <name> - create an object\n");
		gi.cprintf(ent, PRINT_HIGH, " blox activate - activate pointer object\n");
		gi.cprintf(ent, PRINT_HIGH, " blox lock - make the current object solid\n");
		gi.cprintf(ent, PRINT_HIGH, " blox destroy - destroy current object\n");
		gi.cprintf(ent, PRINT_HIGH, " blox movex <i> - move active object\n");
		gi.cprintf(ent, PRINT_HIGH, " blox movey <i> - move active object\n");
		gi.cprintf(ent, PRINT_HIGH, " blox movez <i> - move active object\n");
	} else if(Q_stricmp(cmd, "create") == 0) {
		Blox_Create(ent);
	} else if(Q_stricmp(cmd, "activate") == 0) {
		Blox_MakeActive(ent);
	} else if(Q_stricmp(cmd, "lock") == 0) {
		Blox_Lock(ent);
	} else if(Q_stricmp(cmd, "destroy") == 0) {
		Blox_Destroy(ent);
	} else if(sscanf(cmd, "movex %f", &ftmp) == 1) {
		Blox_MoveActive(ent, ftmp, 0, 0);
	} else if(sscanf(cmd, "movey %f", &ftmp) == 1) {
		Blox_MoveActive(ent, 0, ftmp, 0);
	} else if(sscanf(cmd, "movez %f", &ftmp) == 1) {
		Blox_MoveActive(ent, 0, 0, ftmp);
	} else {
		gi.cprintf(ent, PRINT_HIGH, "Unknown blox command: %s\n", cmd);
	}
}
