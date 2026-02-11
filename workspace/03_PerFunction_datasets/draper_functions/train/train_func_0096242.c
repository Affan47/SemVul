CM2Mesh()
: SkinningBuffers(0), HasAnimation(0), PreparedForSkinning(0),
    AnimationFrames(0.f), LastAnimatedFrame(0.f),
    AnimateNormals(true), HardwareSkinning(0), InterpolationMode(EIM_LINEAR)
{
    #ifdef _DEBUG
    setDebugName("CM2Mesh");
    #endif

    SkinningBuffers=&LocalBuffers;
}
