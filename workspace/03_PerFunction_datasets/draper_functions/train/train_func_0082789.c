parseOverviewFile(char *filename,
		  xmlChar const language [],
		  int debug) {
  xmlDocPtr      doc;
  overviewPtr    ret;
  xmlNodePtr     cur;
  driverEntryPtr driver;


  if (filename == NULL) {
    doc = parseXMLFromStdin();
  } else {
    doc = xmlParseFile(filename);
  }
  if (doc == NULL) return(NULL);


  cur = xmlDocGetRootElement(doc);
  if (cur == NULL) {
    fprintf(stderr,"Empty input document!\n");
    xmlFreeDoc(doc);
    return(NULL);
  }

  if (xmlStrcmp(cur->name, (const xmlChar *) "overview")) {
    fprintf(stderr,"Input document is not a Foomatic overview XML file (no \"<overview>\" tag)!\n");
    xmlFreeDoc(doc);
    return(NULL);
  }


  ret = (overviewPtr) malloc(sizeof(overview));
  if (ret == NULL) {
    fprintf(stderr,"Out of memory!\n");
    xmlFreeDoc(doc);
    return(NULL);
  }
  memset(ret, 0, sizeof(overview));
  ret->num_overviewPrinters = 0;
  ret->overviewPrinters = NULL;


  cur = cur->xmlChildrenNode;
  while (cur) {
    if (xmlIsBlankNode(cur)) {
      cur = cur->next;
      continue;
    }
    if (!xmlStrcmp(cur->name, (const xmlChar *) "driver")) {
      ret->num_overviewDrivers ++;
      ret->overviewDrivers =
	(driverEntryPtr *)realloc
	((driverEntryPtr *)(ret->overviewDrivers),
	 sizeof(driverEntryPtr) * ret->num_overviewDrivers);
      driver = (driverEntryPtr) malloc(sizeof(driverEntry));
      if (driver == NULL) {
	fprintf(stderr,"Out of memory!\n");
	xmlFreeDoc(doc);
	exit(1);
      }
      ret->overviewDrivers[ret->num_overviewDrivers-1] = driver;
      memset(driver, 0, sizeof(driverEntry));
      if (debug) fprintf(stderr, "--> Parsing driver data\n");
      parseDriverEntry(doc, cur, driver, language, debug);
    } else if (!xmlStrcmp(cur->name, (const xmlChar *) "printer")) {
      if (debug) fprintf(stderr, "--> Parsing printer data\n");
      parseOverviewPrinter(doc, cur, ret, language, debug);
    }
    cur = cur->next;
  }


  return(ret);
}
