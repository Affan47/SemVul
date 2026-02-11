autocomplete_command(char *command)
{
    int j = 0;
    struct cli_callback_descr *associated_module = NULL;


    if (strncmp(CLI_SHOW, command, strlen(command)) == 0) {
	printf("%s\n", CLI_SHOW);
	autocomplete_add_token_to_list(CLI_SHOW);
    }
    if (strncmp(CLI_SET, command, strlen(command)) == 0) {
	printf("%s\n", CLI_SET);
	autocomplete_add_token_to_list(CLI_SET);
    }


    while (list_modes[j]) {
	if (strncmp(list_modes[j]->name, command, strlen(command)) == 0) {
	    printf("%s\n", list_modes[j]->name);
	    autocomplete_add_token_to_list(list_modes[j]->name);
	}
	j++;
    }


    j = 0;
    if (current_mode->default_modules && current_mode->default_modules->modules) {
	while (current_mode->default_modules->modules[j].name) {
	    if (strncmp(current_mode->default_modules->modules[j].name,
			command, strlen(command)) == 0) {
		printf("%s\n", current_mode->default_modules->modules[j].name);
		autocomplete_add_token_to_list(current_mode->default_modules->
					       modules[j].name);
	    }
	    j++;
	}
    }


    if (current_mode->mode == HDT_MODE)
	return;

    if (!hdt_mode.default_modules || !hdt_mode.default_modules->modules)
	return;

    j = 0;
    while (hdt_mode.default_modules &&
	   hdt_mode.default_modules->modules[j].name) {


	find_cli_callback_descr(hdt_mode.default_modules->modules[j].name,
				current_mode->default_modules,
				&associated_module);
	if (associated_module == NULL &&
	    strncmp(command,
		    hdt_mode.default_modules->modules[j].name,
		    strlen(command)) == 0) {
	    printf("%s\n", hdt_mode.default_modules->modules[j].name);
	    autocomplete_add_token_to_list(hdt_mode.default_modules->modules[j].
					   name);
	}
	j++;
    }
}
