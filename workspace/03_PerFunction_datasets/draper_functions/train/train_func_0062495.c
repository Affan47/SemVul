interfacesTraversal (GdomeElement *el) {
	GdomeNode *child = NULL;
	GdomeNodeList *nl = NULL;
	GdomeException exc;
  GdomeDOMString *str, *name;
	unsigned long i, nllength;

	nl = gdome_el_childNodes (el, &exc);
	if ((nllength = gdome_nl_length (nl, &exc)) == 0) {
    if (nl != NULL)
			gdome_nl_unref (nl, &exc);
		return;
	}

  name = gdome_str_mkref ("INTERFACE");
	for (i = 0L; i < nllength; i++) {
		child = gdome_nl_item (nl, i, &exc);
		str = gdome_n_nodeName (child, &exc);

		if (gdome_str_equal (str, name)) {
			createInterfaceAPI ((GdomeElement *)child, NULL, 0);
      interfacesTraversal ((GdomeElement *)child);
		}

    gdome_str_unref (str);
		gdome_n_unref (child, &exc);
	}

  gdome_str_unref (name);
	if (nl != NULL)
    gdome_nl_unref (nl, &exc);
}
