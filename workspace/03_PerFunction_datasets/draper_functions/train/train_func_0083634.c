setTechnique(CompositionTechnique* tech, bool reuseTextures)
{
    if (mTechnique != tech)
    {
        if (reuseTextures)
        {


            CompositionTechnique::TextureDefinitionIterator it = mTechnique->getTextureDefinitionIterator();
            while(it.hasMoreElements())
            {
                CompositionTechnique::TextureDefinition *def = it.getNext();
                if (def->pooled)
                {
                    LocalTextureMap::iterator i = mLocalTextures.find(def->name);
                    if (i != mLocalTextures.end())
                    {

                        mReserveTextures[def] = i->second;
                    }

                }
            }
        }

        mTechnique = tech;

        if (mAlive)
        {

            freeResources(false, !reuseTextures);
            createResources(false);

            mChain->_markDirty();
        }

    }
}
