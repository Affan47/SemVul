postTargetOperation(CompositorInstance::TargetOperation &op, Viewport *vp, Camera *cam)
{
    if (cam)
    {
        SceneManager *sm = cam->getSceneManager();

        sm->removeRenderQueueListener(&mOurListener);

        sm->setFindVisibleObjects(mOldFindVisibleObjects);
        cam->setLodBias(mOldLodBias);
    }

    vp->setVisibilityMask(mOldVisibilityMask);
    vp->setMaterialScheme(mOldMaterialScheme);
    vp->setShadowsEnabled(mOldShadowsEnabled);
}
