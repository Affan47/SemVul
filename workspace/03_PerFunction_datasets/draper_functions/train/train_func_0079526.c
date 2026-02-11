generateFpDynamicShadowsHelpers(
        const SM2Profile* prof, const Terrain* terrain, TechniqueType tt, StringStream& outStream)
    {

        outStream <<
            "// Simple PCF \n"
            "// Number of samples in one dimension (square for total samples) \n"
            "#define NUM_SHADOW_SAMPLES_1D 2.0 \n"
            "#define SHADOW_FILTER_SCALE 1 \n"

            "#define SHADOW_SAMPLES NUM_SHADOW_SAMPLES_1D*NUM_SHADOW_SAMPLES_1D \n"

            "float4 offsetSample(float4 uv, float2 offset, float invMapSize) \n"
            "{ \n"
            "   return float4(uv.xy + offset * invMapSize * uv.w, uv.z, uv.w); \n"
            "} \n";


        outStream <<
            "SamplerState ShadowSampler\n"
            "{\n"
            "   Filter = MIN_MAG_MIP_LINEAR;\n"
            "   AddressU = Wrap;\n"
            "   AddressV = Wrap;\n"
            "};\n";

        if (prof->getReceiveDynamicShadowsDepth())
        {
            outStream <<
                "float calcDepthShadow(Texture2D shadowMap, float4 uv, float invShadowMapSize) \n"
                "{ \n"
                "   // 4-sample PCF \n"

                "   float shadow = 0.0; \n"
                "   float offset = (NUM_SHADOW_SAMPLES_1D/2 - 0.5) * SHADOW_FILTER_SCALE; \n"
                "   for (float y = -offset; y <= offset; y += SHADOW_FILTER_SCALE) \n"
                "       for (float x = -offset; x <= offset; x += SHADOW_FILTER_SCALE) \n"
                "       { \n"
                "           float4 newUV = offsetSample(uv, float2(x, y), invShadowMapSize);\n"
                "           // manually project and assign derivatives \n"
                "           // to avoid gradient issues inside loops \n"
                "           newUV = newUV / newUV.w; \n"
                "           float depth = shadowMap.Sample(ShadowSampler, newUV.xy, 1, 1).x; \n"
                "           if (depth >= 1 || depth >= uv.z)\n"
                "               shadow += 1.0;\n"
                "       } \n"

                "   shadow /= SHADOW_SAMPLES; \n"

                "   return shadow; \n"
                "} \n";
        }
        else
        {
            outStream <<
                "float calcSimpleShadow(Texture2D shadowMap, float4 shadowMapPos) \n"
                "{ \n"
                "   // return tex2Dproj(shadowMap,shadowMapPos); "
                "   return shadowMap.Sample(ShadowSampler, shadowMapPos.xy / shadowMapPos.w).x; \n"
                "} \n";

        }

        if (prof->getReceiveDynamicShadowsPSSM())
        {
            uint numTextures = prof->getReceiveDynamicShadowsPSSM()->getSplitCount();


            if (prof->getReceiveDynamicShadowsDepth())
            {
                outStream <<
                    "float calcPSSMDepthShadow(";
            }
            else
            {
                outStream <<
                    "float calcPSSMSimpleShadow(";
            }

            outStream << "\n    ";
            for (uint i = 0; i < numTextures; ++i)
                outStream << "Texture2D shadowMap" << i << ", ";
            outStream << "\n    ";
            for (uint i = 0; i < numTextures; ++i)
                outStream << "float4 lsPos" << i << ", ";
            if (prof->getReceiveDynamicShadowsDepth())
            {
                outStream << "\n    ";
                for (uint i = 0; i < numTextures; ++i)
                    outStream << "float invShadowmapSize" << i << ", ";
            }
            outStream << "\n"
                "   float4 pssmSplitPoints, float camDepth) \n"
                "{ \n"
                "   float shadow; \n"
                "   // calculate shadow \n";

            for (uint i = 0; i < numTextures; ++i)
            {
                if (!i)
                    outStream << "  if (camDepth <= pssmSplitPoints." << ShaderHelper::getChannel(i) << ") \n";
                else if (i < numTextures - 1)
                    outStream << "  else if (camDepth <= pssmSplitPoints." << ShaderHelper::getChannel(i) << ") \n";
                else
                    outStream << "  else \n";

                outStream <<
                    "   { \n";
                if (prof->getReceiveDynamicShadowsDepth())
                {
                    outStream <<
                        "       shadow = calcDepthShadow(shadowMap" << i << ", lsPos" << i << ", invShadowmapSize" << i << "); \n";
                }
                else
                {
                    outStream <<
                        "       shadow = calcSimpleShadow(shadowMap" << i << ", lsPos" << i << "); \n";
                }
                outStream <<
                    "   } \n";

            }

            outStream <<
                "   return shadow; \n"
                "} \n\n\n";
        }


    }
