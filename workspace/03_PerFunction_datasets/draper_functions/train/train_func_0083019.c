rewind(unsigned)
    {
        if(m_num_steps == 0)
        {
            m_step = -1;
            return;
        }
        m_step = m_num_steps;
        m_fx   = m_saved_fx;
        m_fy   = m_saved_fy;
        m_dfx  = m_saved_dfx;
        m_dfy  = m_saved_dfy;
    }
