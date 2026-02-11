ApplyClampExponent(float* rgbaBuffer, long numPixels,
                                const float* exp4)
        {
            for(long pixelIndex=0; pixelIndex<numPixels; ++pixelIndex)
            {
                rgbaBuffer[0] = powf( std::max(0.0f, rgbaBuffer[0]), exp4[0]);
                rgbaBuffer[1] = powf( std::max(0.0f, rgbaBuffer[1]), exp4[1]);
                rgbaBuffer[2] = powf( std::max(0.0f, rgbaBuffer[2]), exp4[2]);
                rgbaBuffer[3] = powf( std::max(0.0f, rgbaBuffer[3]), exp4[3]);
                rgbaBuffer += 4;
            }
        }
