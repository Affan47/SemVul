IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MultistageBehParams") {
        fFreezePhys = tag->getParam("FreezePhys", "false").toBool();
        fSmartSeek = tag->getParam("SmartSeek", "false").toBool();
        fReverseFBControlsOnRelease = tag->getParam("ReverseFBControlsOnRelease", "false").toBool();
    } else if (tag->getName() == "Stages") {
        clearStages();
        fStages.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.getSize(); i++) {
            fStages[i] = new plAnimStage();
            fStages[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Receivers") {
        fReceivers.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
