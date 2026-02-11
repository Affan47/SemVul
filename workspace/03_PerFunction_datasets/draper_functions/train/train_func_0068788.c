IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "GreenAnim") {
        if (tag->hasChildren())
            fGreenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "RedAnim") {
        if (tag->hasChildren())
            fRedAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "OpenAnim") {
        if (tag->hasChildren())
            fOpenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "BounceAnim") {
        if (tag->hasChildren())
            fBounceAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "SoundIndices") {
        fPlaceSoundIdx = tag->getParam("Place", "0").toUint();
        fHitSoundIdx = tag->getParam("Hit", "0").toUint();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
