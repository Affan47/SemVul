freeGlobalTextures()
{
    GlobalTextureMap::iterator i = mGlobalTextures.begin();
    while (i != mGlobalTextures.end())
    {
        TextureManager::getSingleton().remove(i->second->getName());
        ++i;
    }
    mGlobalTextures.clear();

    GlobalMRTMap::iterator mrti = mGlobalMRTs.begin();
    while (mrti != mGlobalMRTs.end())
    {

        Root::getSingleton().getRenderSystem()->destroyRenderTarget(mrti->second->getName());
        ++mrti;
    }
    mGlobalMRTs.clear();

}
