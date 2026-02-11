updateVpParams(
        const SM2Profile* prof, const Terrain* terrain, TechniqueType tt, const GpuProgramParametersSharedPtr& params)
    {
        params->setIgnoreMissingParams(true);
        uint maxLayers = prof->getMaxLayers(terrain);
        uint numLayers = std::min(maxLayers, static_cast<uint>(terrain->getLayerCount()));
        uint numUVMul = numLayers / 4;
        if (numLayers % 4)
            ++numUVMul;
        for (uint i = 0; i < numUVMul; ++i)
        {
            Vector4 uvMul(
                terrain->getLayerUVMultiplier(i * 4),
                terrain->getLayerUVMultiplier(i * 4 + 1),
                terrain->getLayerUVMultiplier(i * 4 + 2),
                terrain->getLayerUVMultiplier(i * 4 + 3)
                );
            params->setNamedConstant("uvMul_" + StringConverter::toString(i), uvMul);
        }

        if (terrain->_getUseVertexCompression() && tt != RENDER_COMPOSITE_MAP)
        {
            Real baseUVScale = 1.0f / (terrain->getSize() - 1);
            params->setNamedConstant("baseUVScale", baseUVScale);
        }

    }
