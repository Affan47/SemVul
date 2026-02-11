hasMaterialAtlasingAttributes(Ogre::Material* material,
                                                                 TextureAtlasAttib* attrib) const
{
    bool isMaterialSpecific = false;
    if ((material) && (material->getNumTechniques()))
    {
        const Ogre::Any& anyAttrib =

            material->getTechnique(0)->getUserObjectBindings().getUserAny(c_RTAtlasKey);
        isMaterialSpecific = (anyAttrib.isEmpty() == false);
        if ((isMaterialSpecific) && (attrib))
        {
            *attrib = Ogre::any_cast<TextureAtlasAttib>(anyAttrib);
        }
    }
    if ((!isMaterialSpecific) && (attrib))
    {
        *attrib = mDefaultAtlasAttrib;
    }
    return isMaterialSpecific;
}
