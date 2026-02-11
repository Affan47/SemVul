IPrcWrite(pfPrcHelper* prc) {
    plRenderTarget::IPrcWrite(prc);

    prc->startTag("DynamicCamMapParams");
    prc->writeParam("Hither", fHither);
    prc->writeParam("Yon", fYon);
    prc->writeParam("FogStart", fFogStart);
    prc->writeParam("RefreshRate", fRefreshRate);
    prc->writeParam("IncCharacters", fIncCharacters);
    prc->endTag();
      fColor.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Camera");
    fCamera->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RootNode");
    fRootNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("TargetNodes");
    for (size_t i=0; i<fTargetNodes.getSize(); i++)
        fTargetNodes[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegionNames");
    for (size_t i=0; i<fVisRegionNames.getSize(); i++) {
        prc->startTag("Region");
        prc->writeParam("Name", fVisRegionNames[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("DisableTexture");
    fDisableTexture->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MatLayers");
    for (size_t i=0; i<fMatLayers.getSize(); i++)
        fMatLayers[i]->prcWrite(prc);
    prc->closeTag();
}
