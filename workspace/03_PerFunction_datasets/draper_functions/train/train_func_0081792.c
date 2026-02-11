symbol_load()
{
	char sym[MAXCOMMAND];
	int i = 0;
	while(!isspace(*(current_command+i+1)) && *(current_command+i+1) != ')')
	{
		sym[i] = *(current_command+i+1);
		++i;
	}
	sym[i++] = '\0';
	add_entry(sym, get_rom_address());
	return 0;
}
