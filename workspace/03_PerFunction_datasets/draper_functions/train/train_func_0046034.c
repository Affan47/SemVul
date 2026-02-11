IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("AGAnimParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->writeParam("EoaFlag", fEoaFlag);
    prc->endTag(true);

    prc->writeSimpleTag("Applicators");
    for (size_t i=0; i<fApps.getSize(); i++) {
        prc->writeSimpleTag("AppSet");
          prc->writeSimpleTag("Applicator");
          fApps[i]->prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Channel");
          fApps[i]->getChannel()->prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();
}
