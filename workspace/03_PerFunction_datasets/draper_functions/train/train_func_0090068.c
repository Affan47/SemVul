createToolBar()
    {
        m_ToolBar = new QToolBar(m_Parent);
#if QT_VERSION > 0x040600
        m_ToolBar->setIconSize(QSize(16,16));
#endif
        m_ToolBar->setFocusPolicy(Qt::ClickFocus);

    }
