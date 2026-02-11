within_trace(double dispersion_pos,
                                        double spatial_pos)
{

    double trace_bottom = cpl_polynomial_eval_1d(m_trace_bottom_pol,
                                                 dispersion_pos, NULL);
    double trace_top    = cpl_polynomial_eval_1d(m_trace_top_pol,
                                                 dispersion_pos, NULL);

    if(spatial_pos >= trace_bottom && spatial_pos <= trace_top)
        return true;

    return false;
}
