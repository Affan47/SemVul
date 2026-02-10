setVideoSurface(QAbstractVideoSurface *surface)
{
    m_surface = surface;

    if (m_control)
        m_control.data()->setSurface(surface);
}
