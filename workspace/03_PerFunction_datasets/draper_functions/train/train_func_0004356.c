xmlSchematronAddTest(xmlSchematronParserCtxtPtr ctxt,
                     xmlSchematronTestType type,
                     xmlSchematronRulePtr rule,
                     xmlNodePtr node, xmlChar *test, xmlChar *report)
{
    xmlSchematronTestPtr ret;
    xmlXPathCompExprPtr comp;

    if ((ctxt == NULL) || (rule == NULL) || (node == NULL) ||
        (test == NULL))
        return(NULL);


    comp = xmlXPathCtxtCompile(ctxt->xctxt, test);
    if (comp == NULL) {
        xmlSchematronPErr(ctxt, node,
            XML_SCHEMAP_NOROOT,
            "Failed to compile test expression %s",
            test, NULL);
        return(NULL);
    }

    ret = (xmlSchematronTestPtr) xmlMalloc(sizeof(xmlSchematronTest));
    if (ret == NULL) {
        xmlSchematronPErrMemory(ctxt, "allocating schema test", node);
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlSchematronTest));
    ret->type = type;
    ret->node = node;
    ret->test = test;
    ret->comp = comp;
    ret->report = report;
    ret->next = NULL;
    if (rule->tests == NULL) {
        rule->tests = ret;
    } else {
        xmlSchematronTestPtr prev = rule->tests;

        while (prev->next != NULL)
             prev = prev->next;
        prev->next = ret;
    }
    return (ret);
}
