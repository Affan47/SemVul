test_document3 (GdomeDocument *doc) {
	GdomeElement *els[4], *root;
	GdomeNode *tel;
	GdomeNodeList *nl;
	GdomeException exc = 0;
	GdomeDOMString *tstr1, *tstr2;
	gboolean ret = TRUE;
	int i;


	for(i=1; i<9; i+=2) {
		tstr1 = gdome_str_mkref_own(g_strdup_printf("%d",i));
		els[i/2] = gdome_doc_getElementById(doc, tstr1, &exc);
		if(els[i/2] == NULL)
			fprintf (stderr, "\nDocument.getElementById(\"%s\"), NULL",tstr1->str), ret = FALSE;
		gdome_str_unref(tstr1);
	}
	dot();


	tstr1 = gdome_str_mkref("NODE");
	tstr2 = gdome_str_mkref("urn:test.tst");
	nl = gdome_doc_getElementsByTagNameNS(doc, tstr2, tstr1, &exc);
	if(nl == NULL)
		fprintf (stderr, "\nDocument.getElementByTagNameNS(\"%s\",\"%s\"), NULL",tstr2->str,tstr1->str), ret = FALSE;
	if(gdome_nl_length(nl, &exc) != 4)
		fprintf (stderr, "\nDocument.getElementByTagNameNS(\"%s\",\"%s\"), wrong length",tstr2->str,tstr1->str), ret = FALSE;
	for(i=0; i<4; i++) {
		tel = gdome_nl_item(nl, (unsigned long)i, &exc);
		if (tel != (GdomeNode *)els[i])
			fprintf (stderr, "\nDocument.getElementByTagName(\"%s\",\"%s\"), wrong %d-th item",tstr2->str,tstr1->str,i), ret = FALSE;
		if (tel != NULL)
			gdome_n_unref (tel, &exc);
	}
	gdome_str_unref(tstr1);
	gdome_str_unref(tstr2);
	dot();


	root = gdome_doc_documentElement (doc, &exc);
  tel = gdome_el_removeChild (root, (GdomeNode *)els[1], &exc);
  gdome_el_unref (els[2], &exc);
  gdome_el_unref (els[1], &exc);
	gdome_n_unref (tel, &exc);
	gdome_el_unref (root, &exc);
	tel = gdome_nl_item(nl, 1L, &exc);
	if(tel != (GdomeNode *)els[3])
		fprintf (stderr, "\nNODELIST IS NOT LIVE!!"), ret = FALSE;
	gdome_n_unref (tel, &exc);
	gdome_nl_unref (nl, &exc);
	dot();

  gdome_el_unref (els[0], &exc);
  gdome_el_unref (els[3], &exc);

	printf ("test_document3\n");
	return ret;
}
