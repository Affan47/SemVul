gen_dump(Entry * head, FILE * fp)
{
    Entry *entry;
    fprintf(fp,
	"static void\n"
	"dump_config(StoreEntry *entry)\n"
	"{\n"
	);
    for (entry = head; entry != NULL; entry = entry->next) {
	assert(entry->loc != NULL);
	if (strcmp(entry->loc, "none") == 0)
	    continue;
	if (strcmp(entry->name, "comment") == 0)
	    continue;
	if (entry->ifdef)
	    fprintf(fp, "#if %s\n", entry->ifdef);
	fprintf(fp, "\tdump_%s(entry, \"%s\", %s);\n",
	    entry->type,
	    entry->name,
	    entry->loc);
	if (entry->ifdef)
	    fprintf(fp, "#endif\n");
    }
    fprintf(fp, "}\n\n");
}
