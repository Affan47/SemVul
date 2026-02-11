gretl_xml_get_submask (xmlNodePtr node, xmlDocPtr doc, char **pmask)
{
    char *mask = NULL;
    int i, len;
    int err = 0;

    if (!gretl_xml_get_prop_as_int(node, "length", &len)) {
	return 1;
    }

    if (len == 0) {
	*pmask = RESAMPLED;
	return 0;
    }

    mask = calloc(len, 1);

    if (mask == NULL) {
	err = 1;
    } else {
	xmlChar *tmp = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
	if (tmp == NULL) {
	    err = 1;
	} else {
	    const char *s = (const char *) tmp;
	    int si;

	    for (i=0; i<len; i++) {
		sscanf(s, "%d", &si);
		s += strspn(s, " ");
		s += strcspn(s, " ");
		if (si != 0) {
		    mask[i] = si;
		}
	    }
	    free(tmp);
	}
    }

    if (!err) {
	*pmask = mask;
    }

    return err;
}
