moveAnimationFrame(int frame)
{
    int cellSize = m_moveTimeLine.endFrame() / (m_foundPath.count()-1);
    int intervalNum = frame/cellSize;

    if(intervalNum == m_foundPath.count()-1)
    {
        m_movingBall->setPos(m_scene->fieldToPix(m_foundPath.last()));
        return;
    }

    int kx=0, ky=0;

    FieldPos from = m_foundPath.at(intervalNum);
    FieldPos to = m_foundPath.at(intervalNum+1);

    if( to.x - from.x > 0 )
        kx = 1;
    else if( to.x - from.x < 0 )
        kx = -1;
    else
        kx = 0;

    if( to.y - from.y > 0 )
        ky = 1;
    else if( to.y - from.y < 0 )
        ky = -1;
    else
        ky = 0;

    int frameWithinInterval = frame%cellSize;
    QPointF pos = m_scene->fieldToPix(from);
    m_movingBall->setPos( pos.x()+kx*frameWithinInterval,
                          pos.y()+ky*frameWithinInterval );
}
