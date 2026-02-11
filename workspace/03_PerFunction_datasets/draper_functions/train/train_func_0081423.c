gn_vcal_file_todo_read(char *filename, gn_todo *ctodo, int number)
{
	FILE *file;
	char type[21] = "", text[258] = "", desc[258] = "";
	char time[16] = "", endtime[16] = "", alarm[16] = "";
	char todo_priority[3] = "", meeting_location[64] = "";


	fprintf(stderr, _("Function %s() is deprecated. Use %s() instead.\n"), __FUNCTION__, "gn_ical2todo");
	file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, _("Can't open file %s for reading!\n"), filename);
		return -1;
	}

	yyin = file;

	memset(ctodo, 0, sizeof(gn_todo));

	if (yylex(type,text,meeting_location,desc,time,endtime,alarm,todo_priority,number)) {
		fprintf(stderr, _("Error parsing vCalendar file!\n"));
		fclose(file);
		return -1;
	}
	gn_todo_fill(ctodo, text, todo_priority);

	fclose(file);
	return 0;
}
