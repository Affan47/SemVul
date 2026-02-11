xmlRelaxNGLogBestError(xmlRelaxNGValidCtxtPtr ctxt)
{
    int best;

    if ((ctxt == NULL) || (ctxt->states == NULL) ||
        (ctxt->states->nbState <= 0))
        return;

    best = xmlRelaxNGBestState(ctxt);
    if ((best >= 0) && (best < ctxt->states->nbState)) {
        ctxt->state = ctxt->states->tabState[best];

        xmlRelaxNGValidateElementEnd(ctxt, 1);
    }
}
