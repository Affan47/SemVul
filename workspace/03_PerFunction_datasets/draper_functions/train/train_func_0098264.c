xmlRelaxNGValidErrorPop(xmlRelaxNGValidCtxtPtr ctxt)
{
    xmlRelaxNGValidErrorPtr cur;

    if (ctxt->errNr <= 0) {
        ctxt->err = NULL;
        return;
    }
    ctxt->errNr--;
    if (ctxt->errNr > 0)
        ctxt->err = &ctxt->errTab[ctxt->errNr - 1];
    else
        ctxt->err = NULL;
    cur = &ctxt->errTab[ctxt->errNr];
    if (cur->flags & ERROR_IS_DUP) {
        if (cur->arg1 != NULL)
            xmlFree((xmlChar *) cur->arg1);
        cur->arg1 = NULL;
        if (cur->arg2 != NULL)
            xmlFree((xmlChar *) cur->arg2);
        cur->arg2 = NULL;
        cur->flags = 0;
    }
}
