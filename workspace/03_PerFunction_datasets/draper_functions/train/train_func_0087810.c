gretl_xml_put_tagged_string (const char *tag, const char *str,
				 FILE *fp)
{
    int err = 0;

    if (str == NULL) {
	return 0;
    }

    if (gretl_xml_validate(str)) {
	fprintf(fp, "<%s>%s</%s>\n", tag, str, tag);
    } else {
	char *xstr = gretl_xml_encode(str);

	if (xstr != NULL) {
	    fprintf(fp, "<%s>%s</%s>\n", tag, xstr, tag);
	    free(xstr);
	} else {
	    err = E_ALLOC;
	}
    }

    return err;
}
