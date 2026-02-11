prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plMorphSpan");

    prc->writeSimpleTag("Deltas");
    for (size_t i=0; i<fDeltas.getSize(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();

    prc->startTag("UVWs");
    prc->writeParam("Channels", fNumUVWChans);
    prc->endTag();
    for (size_t i=0; i<(fDeltas.getSize() * fNumUVWChans); i++)
        fUVWs[i].prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}
