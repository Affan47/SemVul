IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ClothingBaseParams") {
        fName = tag->getParam("Name", "");
        fLayoutName = tag->getParam("Layout", "");
    } else if (tag->getName() == "BaseTexture") {
        if (tag->hasChildren())
            fBaseTexture = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
