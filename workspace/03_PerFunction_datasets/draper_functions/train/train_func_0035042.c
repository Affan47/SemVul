read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    clearSpans();
    fSpans.setSizeNull(S->readInt());
    for (size_t i=0; i<fSpans.getSize(); i++) {
        fSpans[i] = new plGeometrySpan();
        fSpans[i]->read(S);
    }
    fMorphSet = mgr->readKey(S);
    fFlags = S->readByte();
}
