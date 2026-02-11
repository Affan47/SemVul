read(hsStream* S, plClusterGroup* group) {
    fEncoding.read(S);
    fGroup = group;
    unsigned int numVerts = fGroup->getTemplate().getNumVerts();
    clearInstances();
    fInstances.setSizeNull(S->readInt());
    for (size_t i=0; i<fInstances.getSize(); i++) {
        fInstances[i] = new plSpanInstance();
        fInstances[i]->read(S, fEncoding, numVerts);
    }
}
