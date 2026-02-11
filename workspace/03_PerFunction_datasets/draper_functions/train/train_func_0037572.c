clone() const
        {
            OpRcPtr op = OpRcPtr(new ExponentOp(m_exp4, TRANSFORM_DIR_FORWARD));
            return op;
        }
