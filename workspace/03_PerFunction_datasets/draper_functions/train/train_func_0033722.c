IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.getSize(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();
}
