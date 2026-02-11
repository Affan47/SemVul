IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Brain") {
        if (tag->getParam("NULL", "false").toBool())
            setBrain(NULL);
        else if (tag->hasChildren())
            setBrain(plArmatureBrain::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAvTaskMsg::IPrcParse(tag, mgr);
    }
}
