fillPass(
    Pass* gBufferPass, Pass* originalPass, const PassProperties& props)
{

    int texUnitIndex = 0;
    if (props.normalMap != 0)
    {
        *(gBufferPass->getTextureUnitState(texUnitIndex)) = *(props.normalMap);
        texUnitIndex++;
    }
    for (size_t i=0; i<props.regularTextures.size(); i++)
    {
        *(gBufferPass->getTextureUnitState(texUnitIndex)) = *(props.regularTextures[i]);
        texUnitIndex++;
    }
    gBufferPass->setAmbient(originalPass->getAmbient());
    gBufferPass->setDiffuse(originalPass->getDiffuse());
    gBufferPass->setSpecular(originalPass->getSpecular());
    gBufferPass->setShininess(originalPass->getShininess());
    gBufferPass->setCullingMode(originalPass->getCullingMode());
    gBufferPass->setLightingEnabled(false);
}
