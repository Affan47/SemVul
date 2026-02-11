showQuickGuide()
{
    m_aboutBox->close();

    if ( !m_guideDialog ) {
        m_guideDialog = new GuideDialog( m_mainWindow );

        m_guideDialog->resize( m_mainWindow->width() / 2, m_mainWindow->height() - 100 );
        m_guideDialog->move( m_mainWindow->pos().x() + m_mainWindow->width() / 2 - 50, m_mainWindow->pos().y() + 50 );
    }

    m_guideDialog->show();
    m_guideDialog->activateWindow();
}
