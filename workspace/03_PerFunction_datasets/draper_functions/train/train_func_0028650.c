parse_outfile_cmd (const char *s, CMD *cmd)
{
    int len = 0, quoted = 0;

    while (isspace(*s)) {
	s++;
    }

    if (*s) {
	cmd->err = filename_to_param(cmd, s, &len, &quoted);
    }
}
