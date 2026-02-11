slot_removeBadBonus()
{
    m_badBonusCountdownTimer->stop();
    m_badBonusMillisecondsToElapse = 0;

    switch (m_badBonusType)
    {
        case Granatier::Bonus::HYPERACTIVE:
        case Granatier::Bonus::SLOW:
            {
                int askedXSpeedTemp = m_askedXSpeed;
                int askedYSpeedTemp = m_askedYSpeed;
                m_speed = m_normalSpeed;
                m_askedXSpeed = sign(m_xSpeed) * m_speed;
                m_askedYSpeed = sign(m_ySpeed) * m_speed;
                updateDirection();
                m_askedXSpeed = askedXSpeedTemp;
                m_askedYSpeed = askedYSpeedTemp;
            }
            break;
        case Granatier::Bonus::MIRROR:
            {
                int askedXSpeedTemp = m_askedXSpeed;
                int askedYSpeedTemp = m_askedYSpeed;
                m_askedXSpeed = -m_xSpeed;
                m_askedYSpeed = -m_ySpeed;
                switch(m_direction)
                {
                    case Granatier::Direction::EAST:
                        m_direction = Granatier::Direction::WEST;
                        break;
                    case Granatier::Direction::WEST:
                        m_direction = Granatier::Direction::EAST;
                        break;
                    case Granatier::Direction::NORTH:
                        m_direction = Granatier::Direction::SOUTH;
                        break;
                    case Granatier::Direction::SOUTH:
                        m_direction = Granatier::Direction::NORTH;
                        break;
                }
                updateDirection();
                m_askedXSpeed = -askedXSpeedTemp;
                m_askedYSpeed = -askedYSpeedTemp;

                QKeySequence tempKey = m_key.moveLeft;
                m_key.moveLeft = m_key.moveRight;
                m_key.moveRight = tempKey;
                tempKey = m_key.moveUp;
                m_key.moveUp = m_key.moveDown;
                m_key.moveDown = tempKey;

                m_moveMirrored = false;
            }
            break;
        case Granatier::Bonus::RESTRAIN:
            m_bombArmory = m_normalBombArmory;
            break;
        default:
            break;
    }

    bonusUpdated(this, m_badBonusType, 100);
}
