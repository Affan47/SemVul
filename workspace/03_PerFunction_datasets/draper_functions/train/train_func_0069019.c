IPrcWrite(pfPrcHelper* prc) {
    if (fFlags & kHasAgeInfo) {
        prc->writeSimpleTag("AgeInfo");
        fAgeInfo.prcWrite(prc);
        prc->closeTag();
    }
    if (fFlags & kHasLinkingRules) {
        prc->startTag("LinkingRules");
        prc->writeParam("value", fLinkingRules);
        prc->endTag(true);
    }
    if (fFlags & kHasSpawnPt) {
        prc->writeSimpleTag("SpawnPoint");
        fSpawnPoint.prcWrite(prc);
        prc->closeTag();
    }
    if (fFlags & kHasAmCCR) {
        prc->startTag("AmCCR");
        prc->writeParam("value", fAmCCR);
        prc->endTag(true);
    }
    if (fFlags & kHasParentAgeFilename) {
        prc->startTag("ParentAgeFilename");
        prc->writeParam("value", fParentAgeFilename);
        prc->endTag(true);
    }
}
