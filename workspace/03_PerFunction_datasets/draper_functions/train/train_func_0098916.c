getGpuShaderText(const GpuShaderDesc & shaderDesc) const
    {
        AutoMutex lock(m_resultsCacheMutex);

        if(m_lastShaderDesc != shaderDesc.getCacheID())
        {
            m_lastShaderDesc = shaderDesc.getCacheID();
            m_shader = "";
            m_shaderCacheID = "";
            m_lut3D.clear();
            m_lut3DCacheID = "";
        }

        if(m_shader.empty())
        {
            std::ostringstream shader;
            calcGpuShaderText(shader, shaderDesc);
            m_shader = shader.str();

            if(IsDebugLoggingEnabled())
            {
                LogDebug("GPU Shader");
                LogDebug(m_shader);
            }
        }

        return m_shader.c_str();
    }
