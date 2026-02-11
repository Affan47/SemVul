IReadODEPhysical(hsStream* S, plResManager* mgr) {
    fBounds = (plSimDefs::Bounds)S->readInt();

    delete[] fTMDBuffer;
    fTMDBuffer = NULL;

    if (fBounds == plSimDefs::kExplicitBounds) {
        fVerts.setSize(S->readInt());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);
        fIndices.setSize(S->readInt() * 3);
        for (size_t i=0; i<fIndices.getSize(); i++)
            fIndices[i] = S->readInt();
        fTMDSize = S->readInt();
        fTMDBuffer = new unsigned char[fTMDSize];
        S->read(fTMDSize, fTMDBuffer);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fRadius = S->readFloat();
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.read(S);
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        fLength = S->readFloat();
        fRadius = S->readFloat();
    }
    fMass = S->readFloat();

    fMemberGroup = S->readInt();
    fCollideGroup = S->readInt();
    fReportGroup = S->readInt();
    fProps.read(S);
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
}
