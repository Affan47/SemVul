parse_values_between_braces(const char *file, FILE *fp, const char *parameter, cfgStruct cfg[], int *line, cfgFileType type, int section, const char *parameter_buf, int parameter_line)
{
	char *line_buf;
	char *value;
	char *ptr;
	int error_code;

	while ((ptr = get_single_line_without_first_spaces(fp, &line_buf, line)) != NULL) {
		if (*ptr == '}') {
			ptr = rm_first_spaces(ptr + 1);
			if (*ptr != '\0' && *ptr != '#') {
				cfgFatal(CFG_SYNTAX_ERROR, file, *line, line_buf);
				return (CFG_JUST_RETURN_WITHOUT_MSG);
			}
			free(line_buf);
			return (CFG_NO_ERROR);
		}
		if (parse_word(ptr, &value, CFG_VALUE) == NULL) {
			cfgFatal(CFG_SYNTAX_ERROR, file, *line, line_buf);
			return (CFG_JUST_RETURN_WITHOUT_MSG);
		}
		if ((error_code = store_value(cfg, parameter, value, type, section)) != CFG_NO_ERROR) {
			if (error_code == CFG_WRONG_PARAMETER) {
				cfgFatal(error_code, file, parameter_line, parameter_buf);
				return (CFG_JUST_RETURN_WITHOUT_MSG);
			}
			cfgFatal(error_code, file, *line, line_buf);
			return (CFG_JUST_RETURN_WITHOUT_MSG);
		}
		free(line_buf);
		free(value);
	}
	cfgFatal(CFG_NO_CLOSING_BRACE, file, *line, NULL);
	return (CFG_JUST_RETURN_WITHOUT_MSG);
}
