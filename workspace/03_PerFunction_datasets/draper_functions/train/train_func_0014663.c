updateShadows()
{
    setupPixmaps();
    QHash<const QWidget *, Plasma::FrameSvg::EnabledBorders>::const_iterator i;
    for (i = m_windows.constBegin(); i != m_windows.constEnd(); ++i) {
        updateShadow(i.key(), i.value());
    }
}
