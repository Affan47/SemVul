gretl_xml_put_tagged_list (const char *tag, const int *list, FILE *fp)
{
    int i;

    if (list == NULL) {
	return;
    }

    fprintf(fp, "<%s>\n", tag);
    for (i=0; i<=list[0]; i++) {
	if (list[i] == LISTSEP) {
	    fputs("; ", fp);
	} else {
	    fprintf(fp, "%d ", list[i]);
	}
    }
    fprintf(fp, "</%s>\n", tag);
}
