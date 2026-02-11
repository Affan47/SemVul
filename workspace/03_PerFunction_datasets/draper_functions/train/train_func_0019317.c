preAddToRenderState(const RenderState* renderState, Pass* srcPass, Pass* dstPass)
{
    if (srcPass->getLightingEnabled() == false)
        return false;

    mUseSegmentedLightTexture = SegmentedDynamicLightManager::getSingleton().isActive();
    setTrackVertexColourType(srcPass->getVertexColourTracking());

    if (srcPass->getShininess() > 0.0 &&
        srcPass->getSpecular() != ColourValue::Black)
    {
        setSpecularEnable(true);
    }
    else
    {
        setSpecularEnable(false);
    }


    int lightCount[3];
    renderState->getLightCount(lightCount);
    setLightCount(lightCount);

    if (mUseSegmentedLightTexture)
    {
        const_cast<RenderState*>(renderState)->setLightCountAutoUpdate(false);

        Ogre::TextureUnitState* pLightTexture = dstPass->createTextureUnitState();
        pLightTexture->setTextureName(SegmentedDynamicLightManager::getSingleton().getSDLTextureName(), Ogre::TEX_TYPE_2D);
        pLightTexture->setTextureFiltering(Ogre::TFO_NONE);
        mLightSamplerIndex = dstPass->getNumTextureUnitStates() - 1;
    }


    return true;
}
