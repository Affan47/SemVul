recursive_bezier(double x1, double y1,
                                      double x2, double y2,
                                      double x3, double y3,
                                      unsigned level)
    {
        if(level > curve_recursion_limit)
        {
            return;
        }


        double x12   = (x1 + x2) / 2;
        double y12   = (y1 + y2) / 2;
        double x23   = (x2 + x3) / 2;
        double y23   = (y2 + y3) / 2;
        double x123  = (x12 + x23) / 2;
        double y123  = (y12 + y23) / 2;

        double dx = x3-x1;
        double dy = y3-y1;
        double d = fabs(((x2 - x3) * dy - (y2 - y3) * dx));
        double da;

        if(d > curve_collinearity_epsilon)
        {


            if(d * d <= m_distance_tolerance_square * (dx*dx + dy*dy))
            {


                if(m_angle_tolerance < curve_angle_tolerance_epsilon)
                {
                    m_points.add(point_d(x123, y123));
                    return;
                }


                da = fabs(atan2(y3 - y2, x3 - x2) - atan2(y2 - y1, x2 - x1));
                if(da >= pi) da = 2*pi - da;

                if(da < m_angle_tolerance)
                {


                    m_points.add(point_d(x123, y123));
                    return;
                }
            }
        }
        else
        {


            da = dx*dx + dy*dy;
            if(da == 0)
            {
                d = calc_sq_distance(x1, y1, x2, y2);
            }
            else
            {
                d = ((x2 - x1)*dx + (y2 - y1)*dy) / da;
                if(d > 0 && d < 1)
                {


                    return;
                }
                     if(d <= 0) d = calc_sq_distance(x2, y2, x1, y1);
                else if(d >= 1) d = calc_sq_distance(x2, y2, x3, y3);
                else            d = calc_sq_distance(x2, y2, x1 + d*dx, y1 + d*dy);
            }
            if(d < m_distance_tolerance_square)
            {
                m_points.add(point_d(x2, y2));
                return;
            }
        }


        recursive_bezier(x1, y1, x12, y12, x123, y123, level + 1);
        recursive_bezier(x123, y123, x23, y23, x3, y3, level + 1);
    }
