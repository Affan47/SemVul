write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    fPOAOffset.write(S);
    mgr->writeKey(S, fSubject);
    mgr->writeKey(S, fRail);
    if (S->getVer().isNewPlasma()) {
        fEoaFlags.write(S);
    }
    fFlags.write(S);

    S->writeFloat(fAccel);
    S->writeFloat(fDecel);
    S->writeFloat(fVelocity);
    S->writeFloat(fPOAAccel);
    S->writeFloat(fPOADecel);
    S->writeFloat(fPOAVelocity);
    S->writeFloat(fXPanLimit);
    S->writeFloat(fZPanLimit);
    S->writeFloat(fZoomRate);
    S->writeFloat(fZoomMin);
    S->writeFloat(fZoomMax);
}
