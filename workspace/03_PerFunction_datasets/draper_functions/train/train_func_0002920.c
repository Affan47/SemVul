_getUseVertexCompression() const
    {
        return mMaterialGenerator->isVertexCompressionSupported() &&
            TerrainGlobalOptions::getSingleton().getUseVertexCompressionWhenAvailable();
    }
