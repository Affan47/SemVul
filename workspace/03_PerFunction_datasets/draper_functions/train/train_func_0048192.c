xml_put_bundle (gretl_bundle *b, const char *name, FILE *fp)
{
    if (b->creator != NULL && *b->creator != '\0') {
	fprintf(fp, "<gretl-bundle name=\"%s\" creator=\"%s\">\n",
		name, b->creator);
    } else {
	fprintf(fp, "<gretl-bundle name=\"%s\">\n", name);
    }
    g_hash_table_foreach(b->ht, xml_put_bundled_item, fp);
    fputs("</gretl-bundle>\n", fp);
}
