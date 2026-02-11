ss_register_entry(const char *module, int instance, const char *name, int type, void *data, unsigned size)
{
	ss_module *m = ss_get_module(module);
	ss_entry **ep = &(m->instances[instance]);
	ss_entry *e = *ep;
	while((e = *ep) != 0) {
		int pos = strcmp(e->name, name);
		if(!pos) {
			logerror("Duplicate save state registration entry (%s, %d, %s)\n", module, instance, name);
			return NULL;
		}
		if(pos>0)
			break;
		ep = &((*ep)->next);
	}
	*ep = malloc(sizeof(ss_entry));
	if (*ep == NULL) return NULL;
	(*ep)->name = malloc (strlen (name) + 1);
	if ((*ep)->name == NULL) return NULL;
	strcpy ((*ep)->name, name);
	(*ep)->next   = e;
	(*ep)->type   = type;
	(*ep)->data   = data;
	(*ep)->size   = size;
	(*ep)->offset = 0;
	(*ep)->tag	  = ss_current_tag;
	return *ep;
}
