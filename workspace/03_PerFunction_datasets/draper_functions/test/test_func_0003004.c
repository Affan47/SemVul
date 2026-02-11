cfg_find_section(struct CFG_SECTIONS *c, char *name)
{
    struct CFG_ENTRIES* e;
    int i;

    for (i = 0; i < c->sec_count; i++)
	if (0 == strcasecmp(c->sec_names[i],name))
	    return c->sec_entries[i];


    if ((c->sec_count % ALLOC_SIZE) == (ALLOC_SIZE-2)) {
	c->sec_names   = realloc(c->sec_names,(c->sec_count+2+ALLOC_SIZE)*sizeof(char*));
	c->sec_entries = realloc(c->sec_entries,(c->sec_count+2+ALLOC_SIZE)*sizeof(struct CFG_ENTRIES*));
    }
    e = cfg_init_entries();
    c->sec_names[c->sec_count]   = strdup(name);
    c->sec_entries[c->sec_count] = e;
    c->sec_count++;
    c->sec_names[c->sec_count]   = NULL;
    c->sec_entries[c->sec_count] = NULL;
    return e;
}
