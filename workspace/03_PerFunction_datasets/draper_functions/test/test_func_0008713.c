update()
{
    if (m_enableCompass || m_enableAccel) {
        m_stateQError = m_measuredQPose - m_stateQ;
    } else {
        m_stateQError = RTQuaternion();
    }


    RTFLOAT qt = m_Q * m_timeDelta;

    m_stateQ += m_stateQError * (qt / (qt + m_R));

    m_stateQ.normalize();
}
