stringdump(const char *name, const char *member)

{
    indent('\0');
    fprintf(stdout, "\"%s\":", name);
    if (member)
	fprintf(stdout, "\"%s\"", visbuf(member));
    else
	fputs("None", stdout);
    fputs(",\n", stdout);
}
