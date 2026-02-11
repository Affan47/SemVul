writeGpuShader(std::ostream & shader,
                                   const std::string & pixelName,
                                   const GpuShaderDesc & shaderDesc) const
        {
            GpuLanguage lang = shaderDesc.getLanguage();

            if(m_direction == TRANSFORM_DIR_FORWARD)
            {


                float knew[3] = { m_k[0] / logf(m_base[0]),
                                  m_k[1] / logf(m_base[1]),
                                  m_k[2] / logf(m_base[0]) };

                float clampMin[3] = { FLTMIN, FLTMIN, FLTMIN };


                if(lang == GPU_LANGUAGE_CG)
                {
                    clampMin[0] = static_cast<float>(GetHalfNormMin());
                    clampMin[1] = static_cast<float>(GetHalfNormMin());
                    clampMin[2] = static_cast<float>(GetHalfNormMin());
                }


                shader << pixelName << ".rgb = ";
                shader << "max(" << GpuTextHalf3(clampMin,lang) << ", ";
                shader << GpuTextHalf3(m_m,lang) << " * ";
                shader << pixelName << ".rgb + ";
                shader << GpuTextHalf3(m_b,lang) << ");\n";

                shader << pixelName << ".rgb = ";
                shader << GpuTextHalf3(knew,lang) << " * ";
                shader << "log(" << pixelName << ".rgb) + ";
                shader << GpuTextHalf3(m_kb,lang) << ";\n";
            }
            else if(m_direction == TRANSFORM_DIR_INVERSE)
            {
                float kinv[3] = { 1.0f / m_k[0],
                                  1.0f / m_k[1],
                                  1.0f / m_k[2] };

                float minv[3] = { 1.0f / m_m[0],
                                  1.0f / m_m[1],
                                  1.0f / m_m[2] };


                shader << pixelName << ".rgb = ";
                shader << GpuTextHalf3(kinv,lang) << " * (";
                shader << pixelName << ".rgb - ";
                shader << GpuTextHalf3(m_kb,lang) << ");\n";

                shader << pixelName << ".rgb = pow(";
                shader << GpuTextHalf3(m_base,lang) << ", ";
                shader << pixelName << ".rgb);\n";

                shader << pixelName << ".rgb = ";
                shader << GpuTextHalf3(minv,lang) << " * (";
                shader << pixelName << ".rgb - ";
                shader << GpuTextHalf3(m_b,lang) << ");\n";
            }
        }
