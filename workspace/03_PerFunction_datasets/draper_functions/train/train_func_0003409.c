IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundParams") {
        fBegin = tag->getParam("Begin", "0").toFloat();
        fEnd = tag->getParam("End", "0").toFloat();
        fLoop = tag->getParam("Loop", "false").toBool();
        fPlaying = tag->getParam("Playing", "false").toBool();
        fSpeed = tag->getParam("Speed", "0").toFloat();
        fTime = tag->getParam("Time", "0").toFloat();
        fIndex = tag->getParam("Index", "0").toInt();
        fRepeats = tag->getParam("Repeats", "0").toInt();
        fNameStr = tag->getParam("NameStr", "0").toUint();
        fVolume = tag->getParam("Volume", "0").toFloat();
        fFadeType = (FadeType)tag->getParam("FadeType", "0").toInt();
    } else if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else {
        plMessageWithCallbacks::IPrcParse(tag, mgr);
    }
}
