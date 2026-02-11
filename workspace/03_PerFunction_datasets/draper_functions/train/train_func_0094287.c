long_output(index)
	 int             index;
{
	if (!strcmp(object[index]->described, "function")) {
		strcpy(function_name, "long_");
		strcat(function_name, object[index]->label);
		if (execute(function_name) == FALSE) {
			unkfunrun(function_name);
		}


		temp_buffer[0] = 0;
		return (temp_buffer);
	} else {
		return (object[index]->described);
	}
}
