step(int t)
{
    if (m_last == -1) {
        return true;
    }

    int sign = (m_button->brightness() > m_brightness) ? -1 : 1;
    double delta = (t - m_last) * m_speed;

    m_last = t;
    if (fabs(m_button->brightness() - m_brightness) <= delta) {
        m_button->setBrightness(m_brightness);
        return true;
    }
    else {
        m_button->setBrightness(m_button->brightness() + sign * delta);
        return false;
    }
}
