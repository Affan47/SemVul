getPredictedPos() const
{
    WFMath::Point<3> res = (m_moving ? m_predicted.position : m_position);


    return res;
}
