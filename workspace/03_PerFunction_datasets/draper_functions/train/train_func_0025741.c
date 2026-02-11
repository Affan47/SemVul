apply(float* rgbaBuffer, long numPixels) const
        {
            if(!rgbaBuffer) return;
            float exp[4] = { float(m_exp4[0]), float(m_exp4[1]),
                float(m_exp4[2]), float(m_exp4[3]) };
            ApplyClampExponent(rgbaBuffer, numPixels, exp);
        }
