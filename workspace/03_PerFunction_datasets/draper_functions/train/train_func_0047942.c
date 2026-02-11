party_id_read(char *buf, size_t len, int argc, char *argv[], const struct ast_party_id *id)
{
	enum ID_FIELD_STATUS status;

	if (argc == 0) {

		return ID_FIELD_UNKNOWN;
	}

	status = ID_FIELD_VALID;

	if (argc == 1 && !strcasecmp("all", argv[0])) {
		snprintf(buf, len, "\"%s\" <%s>",
			 S_COR(id->name.valid, id->name.str, ""),
			 S_COR(id->number.valid, id->number.str, ""));
	} else if (!strcasecmp("name", argv[0])) {
		status = party_name_read(buf, len, argc - 1, argv + 1, &id->name);
	} else if (!strncasecmp("num", argv[0], 3)) {

		status = party_number_read(buf, len, argc - 1, argv + 1, &id->number);
	} else if (!strncasecmp("subaddr", argv[0], 7)) {

		status = party_subaddress_read(buf, len, argc - 1, argv + 1, &id->subaddress);
	} else if (argc == 1 && !strcasecmp("tag", argv[0])) {
		if (id->tag) {
			ast_copy_string(buf, id->tag, len);
		}
	} else if (argc == 1 && !strcasecmp("ton", argv[0])) {

		snprintf(buf, len, "%d", id->number.plan);
	} else if (argc == 1 && !strncasecmp("pres", argv[0], 4)) {


		ast_copy_string(buf,
			ast_named_caller_presentation(ast_party_id_presentation(id)), len);
	} else {
		status = ID_FIELD_UNKNOWN;
	}

	return status;
}
