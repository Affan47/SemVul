rotateCounterClockwise (void)
{
    if ( !isSatelliteRotating () )
    {
        m_DegreesUntilRotationDone = 90.0f;
        m_RotationDirection = 1.0f;
        if ( m_FallingPair.satellite.y < m_FallingPair.main.y )
        {
            if ( 0 < m_FallingPair.main.x &&
                    0 == getAmoebaAt (m_FallingPair.main.x - 1, m_FallingPair.main.y) )
            {
                m_FallingPair.satellite.x--;
                m_FallingPair.satellite.y++;
            }
            else if ( k_GridWidth - 1 > m_FallingPair.main.x &&
                    0 == getAmoebaAt (m_FallingPair.main.x + 1, m_FallingPair.main.y) )
            {
                m_FallingPair.satellite.y++;
                m_FallingPair.main.x++;
            }
            else
            {

                m_DegreesUntilRotationDone = 0.0f;
            }
        }
        else if ( m_FallingPair.satellite.y > m_FallingPair.main.y )
        {
            if ( k_GridWidth - 1 >  m_FallingPair.main.x &&
                    0 == getAmoebaAt (m_FallingPair.main.x + 1, m_FallingPair.main.y) )
            {
                m_FallingPair.satellite.x++;
                m_FallingPair.satellite.y--;
            }
            else if ( 1 < m_FallingPair.main.x &&
                    0 == getAmoebaAt (m_FallingPair.main.x - 1, m_FallingPair.main.y) )
            {
                m_FallingPair.satellite.y--;
                m_FallingPair.main.x--;
            }
            else
            {

                m_DegreesUntilRotationDone = 0.0f;
            }
        }
        else if ( m_FallingPair.satellite.x < m_FallingPair.main.x )
        {
            if ( 0 == getAmoebaAt (m_FallingPair.main.x, m_FallingPair.main.y + 1) )
            {
                m_FallingPair.satellite.x++;
                m_FallingPair.satellite.y++;
            }
            else
            {

                m_DegreesUntilRotationDone = 0.0f;
            }
        }
        else
        {
            m_FallingPair.satellite.x--;
            m_FallingPair.satellite.y--;
        }
    }
}
