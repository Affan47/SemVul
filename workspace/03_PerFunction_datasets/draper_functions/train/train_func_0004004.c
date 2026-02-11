getAutoconfig(MeshPtr& inMesh, LodConfig& outLodConfig)
{
    outLodConfig.mesh = inMesh;
    outLodConfig.strategy = PixelCountLodStrategy::getSingletonPtr();
    LodLevel lodLevel;
    lodLevel.reductionMethod = LodLevel::VRM_COLLAPSE_COST;
    Real radius = inMesh->getBoundingSphereRadius();
    for(int i = 2; i < 6; i++) {
        Real i4 = (Real) (i * i * i * i);
        Real i5 = i4 * (Real) i;


        lodLevel.distance = 3388608.f / i4;


        lodLevel.reductionValue = radius / 100000.f * i5;
        outLodConfig.levels.push_back(lodLevel);
    }
}
