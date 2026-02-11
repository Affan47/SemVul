_br_find_exe_for_symbol(const void *symbol,
				     GbrInitError * error)
{
#define SIZE PATH_MAX + 100
    FILE *f;
    size_t address_string_len;
    char *address_string, line[SIZE], *found;

    if (symbol == NULL)
	return (char *) NULL;

    f = fopen("/proc/self/maps", "r");
    if (f == NULL)
	return (char *) NULL;

    address_string_len = 4;
    address_string = (char *) g_try_malloc(address_string_len);
    found = (char *) NULL;

    while (!feof(f)) {
	char *start_addr, *end_addr, *end_addr_end, *file;
	void *start_addr_p, *end_addr_p;
	size_t len;

	if (fgets(line, SIZE, f) == NULL)
	    break;


	if (strstr(line, " r-xp ") == NULL || strchr(line, '/') == NULL)
	    continue;


	start_addr = line;
	end_addr = strchr(line, '-');
	file = strchr(line, '/');


	if (!(file > end_addr && end_addr != NULL && end_addr[0] == '-'))
	    continue;

	end_addr[0] = '\0';
	end_addr++;
	end_addr_end = strchr(end_addr, ' ');
	if (end_addr_end == NULL)
	    continue;

	end_addr_end[0] = '\0';
	len = strlen(file);
	if (len == 0)
	    continue;
	if (file[len - 1] == '\n')
	    file[len - 1] = '\0';


	len = strlen(file);
	if (len > 10 && strcmp(file + len - 10, " (deleted)") == 0)
	    file[len - 10] = '\0';


	len = strlen(start_addr);
	if (len != strlen(end_addr))
	    continue;


	if (address_string_len < len + 3) {
	    address_string_len = len + 3;
	    address_string =
		(char *) g_try_realloc(address_string, address_string_len);
	}

	memcpy(address_string, "0x", 2);
	memcpy(address_string + 2, start_addr, len);
	address_string[2 + len] = '\0';
	sscanf(address_string, "%p", &start_addr_p);

	memcpy(address_string, "0x", 2);
	memcpy(address_string + 2, end_addr, len);
	address_string[2 + len] = '\0';
	sscanf(address_string, "%p", &end_addr_p);


	if (symbol >= start_addr_p && symbol < end_addr_p) {
	    found = file;
	    break;
	}
    }

    g_free(address_string);
    fclose(f);

    if (found == NULL)
	return (char *) NULL;
    else
	return g_strdup(found);
}
