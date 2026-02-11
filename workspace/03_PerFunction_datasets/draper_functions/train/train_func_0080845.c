vertex(double* x, double* y)
    {
        unsigned cmd = path_cmd_line_to;
        while(!is_stop(cmd))
        {
            switch(m_status)
            {
            case initial:
                rewind(0);

            case ready:
                if(m_src_vertices.size() < 2 + unsigned(m_closed != 0))
                {
                    cmd = path_cmd_stop;
                    break;
                }
                m_status = outline;
                cmd = path_cmd_move_to;
                m_src_vertex = 0;
                m_out_vertex = 0;

            case outline:
                if(m_src_vertex >= m_src_vertices.size())
                {
                    m_status = end_poly;
                    break;
                }
                m_stroker.calc_join(m_out_vertices,
                                    m_src_vertices.prev(m_src_vertex),
                                    m_src_vertices.curr(m_src_vertex),
                                    m_src_vertices.next(m_src_vertex),
                                    m_src_vertices.prev(m_src_vertex).dist,
                                    m_src_vertices.curr(m_src_vertex).dist);
                ++m_src_vertex;
                m_status = out_vertices;
                m_out_vertex = 0;

            case out_vertices:
                if(m_out_vertex >= m_out_vertices.size())
                {
                    m_status = outline;
                }
                else
                {
                    const point_d& c = m_out_vertices[m_out_vertex++];
                    *x = c.x;
                    *y = c.y;
                    return cmd;
                }
                break;

            case end_poly:
                if(!m_closed) return path_cmd_stop;
                m_status = stop;
                return path_cmd_end_poly | path_flags_close | path_flags_ccw;

            case stop:
                return path_cmd_stop;
            }
        }
        return cmd;
    }
