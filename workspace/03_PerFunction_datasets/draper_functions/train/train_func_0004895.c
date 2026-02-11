resurrect()
{
    int nDirection = dynamic_cast <Player*> (m_model)->direction();
    setZValue(250);
    m_fallingAnimationCounter = 0;
    m_resurrectionAnimationCounter = 10;
    setRenderSize(m_renderSize);
    if(m_renderer->spriteExists("player_0"))
    {
        setSpriteKey("player_0");
    }

    QTransform transform;
    transform.translate(m_itemSizeSet.width() / 2.0, m_itemSizeSet.height() / 2.0);

    switch(nDirection)
    {
        case Granatier::Direction::EAST:
            transform.rotate(0);
            break;
        case Granatier::Direction::SOUTH:
            transform.rotate(90);
            break;
        case Granatier::Direction::NORTH:
            transform.rotate(-90);
            break;
        case Granatier::Direction::WEST:
            transform.rotate(180);
            break;
        default:
            transform.rotate(0);
            break;
    }
    transform.translate(-m_itemSizeReal.width() / 2.0, -m_itemSizeReal.height() / 2.0);
    setTransform(transform);

    startAnim();

    setVisible(true);
}
