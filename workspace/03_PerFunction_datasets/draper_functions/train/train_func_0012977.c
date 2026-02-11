IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "CameraParams") {
        fTransTime = tag->getParam("TransTime", "0").toFloat();
        fActivated = tag->getParam("Activated", "false").toBool();
    } else if (tag->getName() == "NewCam") {
        if (tag->hasChildren())
            fNewCam = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Triggerer") {
        if (tag->hasChildren())
            fTriggerer = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "plCameraConfig") {
        fConfig.prcParse(tag);
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
