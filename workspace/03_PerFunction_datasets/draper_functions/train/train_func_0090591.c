package_write_index (fnpkg *pkg, PRN *prn)
{
    gchar *idxname;
    FILE *fp;

    idxname = g_strdup_printf("%s.xml", pkg->name);

    fp = gretl_fopen(idxname, "w");
    if (fp == NULL) {
	gretl_errmsg_sprintf(_("Couldn't open %s"), idxname);
	g_free(idxname);
	return E_FOPEN;
    }

    gretl_xml_header(fp);

    fputs("<gretl-addon", fp);

    fprintf(fp, " name=\"%s\"", pkg->name);

    if (pkg->dreq == FN_NEEDS_TS) {
	fprintf(fp, " %s=\"true\"", NEEDS_TS);
    } else if (pkg->dreq == FN_NEEDS_QM) {
	fprintf(fp, " %s=\"true\"", NEEDS_QM);
    } else if (pkg->dreq == FN_NEEDS_PANEL) {
	fprintf(fp, " %s=\"true\"", NEEDS_PANEL);
    } else if (pkg->dreq == FN_NODATA_OK) {
	fprintf(fp, " %s=\"true\"", NO_DATA_OK);
    }

    if (pkg->modelreq > 0) {
	fprintf(fp, " model-requirement=\"%s\"",
		gretl_command_word(pkg->modelreq));
    }

    if (pkg->minver > 0) {
	char vstr[8];

	fprintf(fp, " minver=\"%s\"", get_version_string(vstr, pkg->minver));
    }

    if (pkg->uses_subdir) {
	fprintf(fp, " lives-in-subdir=\"true\"");
    }

    fputs(">\n", fp);

    gretl_xml_put_tagged_string("author",  pkg->author, fp);
    gretl_xml_put_tagged_string("version", pkg->version, fp);
    gretl_xml_put_tagged_string("date",    pkg->date, fp);
    gretl_xml_put_tagged_string("description", pkg->descrip, fp);

    if (pkg->label != NULL) {
	gretl_xml_put_tagged_string("label", pkg->label, fp);
    }

    if (pkg->mpath != NULL) {
	gretl_xml_put_tagged_string("menu-attachment", pkg->mpath, fp);
    }

    fputs("</gretl-addon>\n", fp);

    fclose(fp);

    pprintf(prn, "Wrote index file %s\n", idxname);
    g_free(idxname);

    return 0;
}
