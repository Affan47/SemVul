IsLut1DNoOp(const Lut1D & lut,
                         float maxerror,
                         ErrorType errortype)
        {

            if(!(maxerror > 0.0)) return false;

            for(int channel = 0; channel<3; ++channel)
            {
                if(lut.luts[channel].size() == 0) continue;

                float inorm = 1.0f / (static_cast<float>(lut.luts[channel].size()) - 1.0f);

                float m = lut.from_max[channel] - lut.from_min[channel];
                float b = lut.from_min[channel];

                for(unsigned int i=0; i<lut.luts[channel].size(); ++i)
                {
                    float x = static_cast<float>(i) * inorm;
                    float identval = m*x+b;
                    float lutval = lut.luts[channel][i];

                    if(errortype == ERROR_ABSOLUTE)
                    {
                        if(!equalWithAbsError(identval, lutval, maxerror))
                        {
                            return false;
                        }
                    }
                    else if(errortype == ERROR_RELATIVE)
                    {
                        if(!equalWithRelError(identval, lutval, maxerror))
                        {
                            return false;
                        }
                    }
                    else
                    {
                        throw Exception("Unknown error type.");
                    }
                }
            }

            return true;
        }
