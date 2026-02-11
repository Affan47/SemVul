IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SceneObjects") {
        fSceneObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSceneObjects.getSize(); i++) {
            fSceneObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PoolObjects") {
        fPoolObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPoolObjects.getSize(); i++) {
            fPoolObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
