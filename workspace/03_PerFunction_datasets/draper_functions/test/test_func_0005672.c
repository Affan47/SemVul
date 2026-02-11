ajDomDocumentCreateProcessingInstruction(AjPDomDocument doc,
                                                  const AjPStr target,
                                                  const AjPStr data)
{
    if(!target || !data)
        return NULL;

    return ajDomDocumentCreateProcessingInstructionC(doc, MAJSTRGETPTR(target),
                                                     MAJSTRGETPTR(data));
}
