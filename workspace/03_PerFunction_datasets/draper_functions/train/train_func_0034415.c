windowsAt(int index) const
{
    if (index < 0 || index >= m_windows.count())
        return 0;

    return qobject_cast<WindowModel *>(m_windows[index]);
}
