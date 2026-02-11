destroyShadowTextures(void)
    {
        size_t count = mShadowTextureCameras.size();
        for (size_t i = 0; i < count; ++i)
        {
            SceneNode* node = mShadowTextureCameras[i]->getParentSceneNode();
            mSceneRoot->removeAndDestroyChild(node->getName());
        }
        SceneManager::destroyShadowTextures();
    }
