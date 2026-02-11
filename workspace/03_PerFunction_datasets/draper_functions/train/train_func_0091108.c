er_paf_read_whole_file(const char * paf_config_filename)
    {
    FILE * file_descriptor;
    char line[MAXSTRLENCONF];
    er_stringarray_t * file_buffer;


    file_buffer = er_stringarray_new();


    file_descriptor = fopen(paf_config_filename, "r");
    if (file_descriptor == NULL)
	return NULL;
    memset(line, 0, MAXSTRLENCONF);

    while (fgets(line, MAXSTRLENCONF -1, file_descriptor) != NULL)
	{

	er_stringarray_append(file_buffer, line);

	memset(line, '\0', MAXSTRLENCONF);
	}

    fclose(file_descriptor);
    return file_buffer;
    }
