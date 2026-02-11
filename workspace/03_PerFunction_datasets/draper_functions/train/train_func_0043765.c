IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Constants") {
        const pfPrcTag* child = tag->getFirstChild();
        fConsts.setSize(tag->countChildren());
        for (size_t i=0; i<fConsts.getSize(); i++) {
            fConsts[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ShaderParams") {
        fID = (plShaderID)tag->getParam("ID", "0").toUint();
        fInput = tag->getParam("Input", "0").toUint();
        fOutput = tag->getParam("Output", "0").toUint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
