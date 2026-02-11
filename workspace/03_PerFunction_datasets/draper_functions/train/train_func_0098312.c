write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSceneObjects.getSize());
    for (size_t i=0; i<fSceneObjects.getSize(); i++)
        mgr->writeKey(S, fSceneObjects[i]);
    S->writeInt(fPoolObjects.getSize());
    for (size_t i=0; i<fPoolObjects.getSize(); i++)
        mgr->writeKey(S, fPoolObjects[i]);
}
