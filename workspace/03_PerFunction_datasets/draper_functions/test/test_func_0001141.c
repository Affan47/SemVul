vertex(double* x, double* y)
    {
        if(m_step < 0) return path_cmd_stop;
        if(m_step == m_num_steps)
        {
            *x = m_start_x;
            *y = m_start_y;
            --m_step;
            return path_cmd_move_to;
        }

        if(m_step == 0)
        {
            *x = m_end_x;
            *y = m_end_y;
            --m_step;
            return path_cmd_line_to;
        }

        m_fx   += m_dfx;
        m_fy   += m_dfy;
        m_dfx  += m_ddfx;
        m_dfy  += m_ddfy;
        m_ddfx += m_dddfx;
        m_ddfy += m_dddfy;

        *x = m_fx;
        *y = m_fy;
        --m_step;
        return path_cmd_line_to;
    }
