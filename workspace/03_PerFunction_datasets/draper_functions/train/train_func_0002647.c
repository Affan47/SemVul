check2(int argc, char **argv) {
  xmlDocPtr doc=NULL;
  xmlNodePtr root_node = NULL;
  xmlNodePtr node = NULL;

  const char *s;
  int rv;

  GWEN_Logger_Open(AQEBICS_LOGDOMAIN, "aqebics", 0,
                   GWEN_LoggerType_Console,
                   GWEN_LoggerFacility_User);
  GWEN_Logger_SetLevel(AQEBICS_LOGDOMAIN, GWEN_LoggerLevel_Info);

  doc=xmlNewDoc(BAD_CAST "1.0");
  root_node=xmlNewNode(NULL, BAD_CAST "ebics");
  xmlDocSetRootElement(doc, root_node);

  node=xmlNewChild(root_node, NULL, BAD_CAST "test1", NULL);
  xmlNewChild(node, NULL, BAD_CAST "test2", BAD_CAST "valueOf2");
  xmlNewChild(node, NULL, BAD_CAST "test3", NULL);
  xmlNewChild(node, NULL, BAD_CAST "test4", NULL);
  node=xmlNewChild(root_node, NULL, BAD_CAST "test5", NULL);

  s=EB_Xml_GetCharValue(root_node, "test1/test2", 0);
  if (!s) {
    fprintf(stderr, "FAILED: Value of \"test2\" not found\n");
    return 3;
  }
  if (strcmp(s, "valueOf2")!=0) {
    fprintf(stderr, "FAILED: Bad value of \"test2\": [%s]\n", s);
    return 3;
  }

  rv=EB_Xml_SetCharValue(root_node, "test1/test3", "valueOf3");
  if (rv) {
    fprintf(stderr, "FAILED: Could not set value of \"test3\"\n");
    return 3;
  }
  s=EB_Xml_GetCharValue(root_node, "test1/test3", 0);
  if (!s) {
    fprintf(stderr, "FAILED: Value of \"test3\" not found\n");
    return 3;
  }
  if (strcmp(s, "valueOf3")!=0) {
    fprintf(stderr, "FAILED: Bad value of \"test3\": [%s]\n", s);
    return 3;
  }


  s=EB_Xml_GetCharValue(root_node, "test1/test2", 0);
  if (!s) {
    fprintf(stderr, "FAILED: Value of \"test2\" not found (2)\n");
    return 3;
  }
  if (strcmp(s, "valueOf2")!=0) {
    fprintf(stderr, "FAILED: Bad value of \"test2\": [%s] (2)\n", s);
    return 3;
  }

  rv=EB_Xml_SetCharValue(root_node, "test4", "valueOf4");
  if (rv) {
    fprintf(stderr, "FAILED: Could not set value of \"test4\"\n");
    return 3;
  }
  s=EB_Xml_GetCharValue(root_node, "test4", 0);
  if (!s) {
    fprintf(stderr, "FAILED: Value of \"test4\" not found\n");
    return 3;
  }
  if (strcmp(s, "valueOf4")!=0) {
    fprintf(stderr, "FAILED: Bad value of \"test4\": [%s]\n", s);
    return 3;
  }

  fprintf(stderr, "Check2: PASSED.\n");
  return 0;
}
