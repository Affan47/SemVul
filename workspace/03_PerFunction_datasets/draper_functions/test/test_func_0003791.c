getGpuLut3D(float* lut3d, const GpuShaderDesc & shaderDesc) const
    {
        if(!lut3d) return;

        AutoMutex lock(m_resultsCacheMutex);

        if(m_lastShaderDesc != shaderDesc.getCacheID())
        {
            m_lastShaderDesc = shaderDesc.getCacheID();
            m_shader = "";
            m_shaderCacheID = "";
            m_lut3D.clear();
            m_lut3DCacheID = "";
        }

        int lut3DEdgeLen = shaderDesc.getLut3DEdgeLen();
        int lut3DNumPixels = lut3DEdgeLen*lut3DEdgeLen*lut3DEdgeLen;


        if(m_gpuOpsCpuLatticeProcess.empty())
        {
            memset(lut3d, 0, sizeof(float) * 3 * lut3DNumPixels);
            return;
        }

        if(m_lut3D.empty())
        {

            m_lut3D.resize(lut3DNumPixels*4);
            GenerateIdentityLut3D(&m_lut3D[0], lut3DEdgeLen, 4, LUT3DORDER_FAST_RED);


            for(int i=0; i<(int)m_gpuOpsCpuLatticeProcess.size(); ++i)
            {
                m_gpuOpsCpuLatticeProcess[i]->apply(&m_lut3D[0], lut3DNumPixels);
            }


            for(int i=1; i<lut3DNumPixels; ++i)
            {
                m_lut3D[3*i+0] = m_lut3D[4*i+0];
                m_lut3D[3*i+1] = m_lut3D[4*i+1];
                m_lut3D[3*i+2] = m_lut3D[4*i+2];
            }
        }


        memcpy(lut3d, &m_lut3D[0], sizeof(float) * 3 * lut3DNumPixels);
    }
