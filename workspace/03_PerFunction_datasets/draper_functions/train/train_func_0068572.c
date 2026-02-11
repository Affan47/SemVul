IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Callback");
    fCallback->prcWrite(prc);
    prc->closeTag();
}
