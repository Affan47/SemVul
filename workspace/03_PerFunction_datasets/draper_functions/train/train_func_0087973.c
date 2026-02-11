addValToSets(UVector *sets, uint32_t val) {
    int32_t       ix;

    for (ix=0; ix<sets->size(); ix++) {
        RBBINode *usetNode = (RBBINode *)sets->elementAt(ix);
        addValToSet(usetNode, val);
    }
}
