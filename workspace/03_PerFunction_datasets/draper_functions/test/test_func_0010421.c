clone() const
        {
            OpRcPtr op = OpRcPtr(new Lut3DOp(m_lut, m_interpolation, m_direction));
            return op;
        }
