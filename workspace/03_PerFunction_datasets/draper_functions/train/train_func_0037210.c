df_gets()
{
    int len = 0;


    if (mixed_data_fp && interactive)
	fputs("input data ('e' ends) > ", stderr);


    if (df_pseudodata)
	return df_generate_pseudodata();

    if (!fgets(line, max_line_len, data_fp))
	return NULL;

    if (mixed_data_fp)
	++inline_num;

    for (;;) {
	len += strlen(line + len);

	if (len > 0 && line[len - 1] == '\n') {


	    line[len - 1] = 0;
	    return line;
	}


	if ((max_line_len - len) < 32)
	    line = gp_realloc(line, max_line_len *= 2, "datafile line buffer");

	if (!fgets(line + len, max_line_len - len, data_fp))
	    return line;
    }


    return NULL;
}
