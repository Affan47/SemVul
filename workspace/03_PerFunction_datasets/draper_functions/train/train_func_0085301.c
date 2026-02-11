perl_script_find(const char *name)
{
	GSList *tmp;

        g_return_val_if_fail(name != NULL, NULL);

	for (tmp = perl_scripts; tmp != NULL; tmp = tmp->next) {
		PERL_SCRIPT_REC *rec = tmp->data;

		if (strcmp(rec->name, name) == 0)
                        return rec;
	}

        return NULL;
}
