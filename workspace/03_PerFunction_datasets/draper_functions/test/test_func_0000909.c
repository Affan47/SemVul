SetLambdaMap( const int level , const TwoDArray<float>& l_map , const float wt )
{

    const int factor = 1<<(2-level);
    int xstart , xend , ystart , yend;

    for (int j = 0 ; j<m_lambda_map.LengthY() ; ++j )
    {
        for (int i = 0 ; i<m_lambda_map.LengthX() ; ++i )
        {
            xstart = factor * i;
            ystart = factor * j;
            xend = factor * ( i + 1 );
            yend = factor * ( j + 1 );

            m_lambda_map[j][i] = l_map[ystart][xstart];

            for (int q = ystart ; q<yend ; ++q )
                for (int p = xstart ; p<xend ; ++p )
                      m_lambda_map[j][i] = std::max( l_map[q][p] , m_lambda_map[j][i] );

           m_lambda_map[j][i] *= wt;

        }
    }

}
