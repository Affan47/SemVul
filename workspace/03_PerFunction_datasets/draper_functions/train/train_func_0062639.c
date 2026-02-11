IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Sender");
    fSender->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("MessageParams");
    prc->writeParam("TimeStamp", fTimeStamp);
    prc->writeParamHex("BCastFlags", fBCastFlags);
    prc->endTag(true);
}
