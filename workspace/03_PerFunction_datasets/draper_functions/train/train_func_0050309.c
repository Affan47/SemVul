DoLevelDecn( int level )
{


    const int xstart = m_xsb_loc <<level;
    const int ystart = m_ysb_loc <<level;

    const int xend = xstart + (1<<level);
    const int yend = ystart + (1<<level);


    float SB_cost = 0.0;
    for ( int j=ystart ; j<yend ; ++j)
    {
        for (int i=xstart ; i<xend ; ++i)
       {
           if ( level<2 )
               DoME( i , j , level);
            SB_cost += DoUnitDecn( i , j ,level );

        }
    }


    if (level == 2)
    {
        m_me_data_set[2]->SBSplit()[m_ysb_loc][m_xsb_loc] = 2;
        m_me_data_set[2]->SBCosts()[m_ysb_loc][m_xsb_loc] = SB_cost;
    }

    if ( level<2 && SB_cost <= m_me_data_set[2]->SBCosts()[m_ysb_loc][m_xsb_loc] )
    {
        m_me_data_set[2]->SBCosts()[m_ysb_loc][m_xsb_loc] = SB_cost;
        m_me_data_set[2]->SBSplit()[m_ysb_loc][m_xsb_loc] = level;


        int xblock_start;
        int yblock_start;
        int xblock_end;
        int yblock_end;

        for ( int j=ystart ; j<yend ; ++j )
        {
            yblock_start = j<<(2-level);
            yblock_end = (j+1)<<(2-level);
            for ( int i=xstart ; i<xend ; ++i )
            {
                xblock_start = i<<(2-level);
                xblock_end = (i+1)<<(2-level);

                for ( int v=yblock_start ; v<yblock_end ; ++v )
                {
                    for ( int u=xblock_start ; u<xblock_end ; ++u )
                    {
                        m_me_data_set[2]->Mode()[v][u] = m_me_data_set[level]->Mode()[j][i];
                        m_me_data_set[2]->DC( Y_COMP )[v][u] = m_me_data_set[level]->DC( Y_COMP )[j][i];
                        m_me_data_set[2]->Vectors(1)[v][u] = m_me_data_set[level]->Vectors(1)[j][i];
                        if ( num_refs>1 )
                            m_me_data_set[2]->Vectors(2)[v][u] = m_me_data_set[level]->Vectors(2)[j][i];

                    }
                }

            }
        }

    }

}
