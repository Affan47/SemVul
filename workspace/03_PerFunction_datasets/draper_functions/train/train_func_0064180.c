xmlRelaxNGCheckCycles(xmlRelaxNGParserCtxtPtr ctxt,
                      xmlRelaxNGDefinePtr cur, int depth)
{
    int ret = 0;

    while ((ret == 0) && (cur != NULL)) {
        if ((cur->type == XML_RELAXNG_REF) ||
            (cur->type == XML_RELAXNG_PARENTREF)) {
            if (cur->depth == -1) {
                cur->depth = depth;
                ret = xmlRelaxNGCheckCycles(ctxt, cur->content, depth);
                cur->depth = -2;
            } else if (depth == cur->depth) {
                xmlRngPErr(ctxt, cur->node, XML_RNGP_REF_CYCLE,
                           "Detected a cycle in %s references\n",
                           cur->name, NULL);
                return (-1);
            }
        } else if (cur->type == XML_RELAXNG_ELEMENT) {
            ret = xmlRelaxNGCheckCycles(ctxt, cur->content, depth + 1);
        } else {
            ret = xmlRelaxNGCheckCycles(ctxt, cur->content, depth);
        }
        cur = cur->next;
    }
    return (ret);
}
