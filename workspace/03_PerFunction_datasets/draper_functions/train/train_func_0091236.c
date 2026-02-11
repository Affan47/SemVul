setMaterialAtlasingAttributes(Ogre::Material* material,
        IndexPositionMode mode, ushort offset, bool autoAdjustBorders)
{
    if ((material) && (material->getNumTechniques()))
    {
        material->getTechnique(0)->getUserObjectBindings().setUserAny(c_RTAtlasKey,
            Ogre::Any(TextureAtlasAttib(mode, offset, autoAdjustBorders)));
    }
}
