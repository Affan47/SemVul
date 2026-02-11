isSupported() const
{
    if (!m_resources)
        return false;


    for (int o = 0; o < m_resources->noutput; o++)
    {
        if (backlight_get(m_resources->outputs[o]) != -1) {
            return true;
        }
    }

    return false;
}
