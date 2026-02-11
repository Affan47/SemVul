message_template_build(const char *name, struct ast_variable *var)
{
	struct minivm_template *template;
	int error = 0;

	template = message_template_create(name);
	if (!template) {
		ast_log(LOG_ERROR, "Out of memory, can't allocate message template object %s.\n", name);
		return -1;
	}

	while (var) {
		ast_debug(3, "Configuring template option %s = \"%s\" for template %s\n", var->name, var->value, name);
		if (!strcasecmp(var->name, "fromaddress")) {
			ast_copy_string(template->fromaddress, var->value, sizeof(template->fromaddress));
		} else if (!strcasecmp(var->name, "fromemail")) {
			ast_copy_string(template->serveremail, var->value, sizeof(template->serveremail));
		} else if (!strcasecmp(var->name, "subject")) {
			ast_copy_string(template->subject, var->value, sizeof(template->subject));
		} else if (!strcasecmp(var->name, "locale")) {
			ast_copy_string(template->locale, var->value, sizeof(template->locale));
		} else if (!strcasecmp(var->name, "attachmedia")) {
			template->attachment = ast_true(var->value);
		} else if (!strcasecmp(var->name, "dateformat")) {
			ast_copy_string(template->dateformat, var->value, sizeof(template->dateformat));
		} else if (!strcasecmp(var->name, "charset")) {
			ast_copy_string(template->charset, var->value, sizeof(template->charset));
		} else if (!strcasecmp(var->name, "templatefile")) {
			if (template->body)
				ast_free(template->body);
			template->body = message_template_parse_filebody(var->value);
			if (!template->body) {
				ast_log(LOG_ERROR, "Error reading message body definition file %s\n", var->value);
				error++;
			}
		} else if (!strcasecmp(var->name, "messagebody")) {
			if (template->body)
				ast_free(template->body);
			template->body = message_template_parse_emailbody(var->value);
			if (!template->body) {
				ast_log(LOG_ERROR, "Error parsing message body definition:\n          %s\n", var->value);
				error++;
			}
		} else {
			ast_log(LOG_ERROR, "Unknown message template configuration option \"%s=%s\"\n", var->name, var->value);
			error++;
		}
		var = var->next;
	}
	if (error)
		ast_log(LOG_ERROR, "-- %d errors found parsing message template definition %s\n", error, name);

	AST_LIST_LOCK(&message_templates);
	AST_LIST_INSERT_TAIL(&message_templates, template, list);
	AST_LIST_UNLOCK(&message_templates);

	global_stats.templates++;

	return error;
}
