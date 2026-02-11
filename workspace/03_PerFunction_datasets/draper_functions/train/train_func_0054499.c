destroyRenderTarget(RenderTarget* target)
    {
        detachRenderTarget(target);
        OGRE_DELETE target;
    }
