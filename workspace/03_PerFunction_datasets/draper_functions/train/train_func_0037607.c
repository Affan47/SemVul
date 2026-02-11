frameRenderingQueued( const FrameEvent& evt )
{
    if (mSceneMgr->hasLight(SPOT_LIGHT_NAME))
    {
        Light* light = mSceneMgr->getLight(SPOT_LIGHT_NAME);

        light->setPosition(mCamera->getDerivedPosition() + mCamera->getDerivedUp() * 20.0);
        light->setDirection(mCamera->getDerivedDirection());
    }

    if (mPointLightNode != NULL)
    {
        static Real sToatalTime = 0.0;

        sToatalTime += evt.timeSinceLastFrame;
        mPointLightNode->yaw(Degree(evt.timeSinceLastFrame * 15));
        mPointLightNode->setPosition(0.0, Math::Sin(sToatalTime) * 30.0, 0.0);
    }

    updateTargetObjInfo();

    return SdkSample::frameRenderingQueued(evt);
}
