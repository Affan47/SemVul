getNextPair (void)
{
    assert ( 0 != m_Generator &&
            "Tried to get the next pair without a generator.");
    assert ( 2 <= m_InactiveAmoebas.size () &&
            "Tried to get the next pair, but the inactive list is empty.");


    Amoeba *main = m_InactiveAmoebas.front ();
    m_InactiveAmoebas.pop_front ();
    Amoeba *satellite = m_InactiveAmoebas.front ();
    m_InactiveAmoebas.pop_front ();

    m_QueuedAmoebas.push_back (main);
    m_QueuedAmoebas.push_back (satellite);


    uint16_t lastPairOffsetX = getAmoebaSize () / 2;
    if ( LayoutVertical == getLayout () )
    {
        if ( Grid::QueueSideLeft == getQueueSide () )
        {
            lastPairOffsetX = -lastPairOffsetX;
        }
        main->setX (getQueuePositionX () + lastPairOffsetX);
        main->setY (getQueuePositionY () + getAmoebaSize () * 3);
        satellite->setX (getQueuePositionX () + lastPairOffsetX);
        satellite->setY (getQueuePositionY () + getAmoebaSize () * 2);
    }
    else
    {
        if (Grid::QueueSideLeft == getQueueSide () )
        {
            main->setX (getQueuePositionX () - getAmoebaSize () * 4);
            main->setY (getQueuePositionY () + lastPairOffsetX);
            satellite->setX (getQueuePositionX () - getAmoebaSize () * 3);
            satellite->setY (getQueuePositionY () + lastPairOffsetX);
        }
        else
        {
            main->setX (getQueuePositionX () + getAmoebaSize () * 3);
            main->setY (getQueuePositionY () - getAmoebaSize () - lastPairOffsetX);
            satellite->setX (getQueuePositionX () + getAmoebaSize () * 2);
            satellite->setY (getQueuePositionY () - getAmoebaSize () - lastPairOffsetX);
        }
    }

    FallingPair fallingPair;
    fallingPair.main.amoeba = main;
    fallingPair.main.x = 3;
    fallingPair.main.y = k_FirstVisibleHeight - 2;
    fallingPair.satellite.amoeba = satellite;
    fallingPair.satellite.x = 3;
    fallingPair.satellite.y = k_FirstVisibleHeight - 3;
    fallingPair.verticalOffset = 0;
    fallingPair.fallingTime = k_DefaultFallingTime;
    m_Queue.push_back (fallingPair);

    if ( m_InactiveAmoebas.empty () )
    {
        m_Generator->generate ();
    }
}
