xmlSchematronReportPattern(xmlSchematronValidCtxtPtr ctxt,
                           xmlSchematronPatternPtr pattern) {
    if ((ctxt == NULL) || (pattern == NULL))
        return;
    if (ctxt->flags & XML_SCHEMATRON_OUT_QUIET)
        return;
    if (ctxt->flags & XML_SCHEMATRON_OUT_XML) {
        TODO
    } else {
        char msg[1000];

        if (pattern->name == NULL)
            return;
        snprintf(msg, 999, "Pattern: %s\n", (const char *) pattern->name);
        xmlSchematronReportOutput(ctxt, NULL, &msg[0]);
    }
}
