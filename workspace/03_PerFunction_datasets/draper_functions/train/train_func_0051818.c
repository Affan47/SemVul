IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Template") {
        if (tag->hasChildren())
            fTemplate.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Clusters") {
        clearClusters();
        fClusters.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fClusters.getSize(); i++) {
            fClusters[i] = new plCluster();
            fClusters[i]->prcParse(child, this);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Regions") {
        fRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.getSize(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Lights") {
        fLights.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLights.getSize(); i++) {
            fLights[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LOD") {
        if (tag->hasChildren())
            fLOD.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "RenderLevel") {
        fRenderLevel = tag->getParam("Level", "0").toUint();
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
