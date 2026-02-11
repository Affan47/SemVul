delete_point(const double Px, const double Py )
{
    for ( int i = 0; i < _nof_points; i++ )
    {
        if ( ( fabs(Px - x[i]) <= _tx ) && ( fabs(Py - y[i]) <= _ty ) )
        {
            for ( int j = i; j < _nof_points - 1; j++ )
            {
                x[j] = x[j+1];
                y[j] = y[j+1];
                for ( int k = 0; k < _nof_vars; k++ )
                    rhs[k][j+3] = rhs[k][j+3+1];
            }
            _nof_points--;
            type = VIZ_GEOREF_SPLINE_POINT_WAS_DELETED;
            return(1);
        }
    }
    return(0);
}
