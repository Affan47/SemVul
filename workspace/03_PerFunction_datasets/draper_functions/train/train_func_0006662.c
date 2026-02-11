setTopBarEnabled(bool enabled)
{
    if (enabled == m_topBarEnabled)
        return;
    m_topBarEnabled = enabled;
    m_foreColorPicker->setVisible(m_topBarEnabled || m_bottomBarEnabled);
    update();
}
