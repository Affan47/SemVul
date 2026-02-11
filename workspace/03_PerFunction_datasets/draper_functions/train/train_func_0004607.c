setShift(const V2 &shift)
{
    m_shift = shift;
    int width = 0;
    t_widgets::iterator end = m_widgets.end();
    for (t_widgets::iterator i = m_widgets.begin(); i != end; ++i) {
        (*i)->setShift(m_shift.plus(V2(width, 0)));
        width += (*i)->getW();
    }
}
