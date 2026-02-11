screenGeometryChanged(int)
{
    int i;

    for (i = 0; i < m_desktop->screenCount(); i++) {
        if (i < m_windows.count()) {
            m_windows[i]->setGeometry(m_desktop->availableGeometry(i));
        }
        else {
            SplashWindow *w = new SplashWindow(m_testing);


            if (w->status() == QDeclarativeView::Error) {
                ::exit(2);
            }
            w->setGeometry(m_desktop->availableGeometry(i));
            w->setStage(m_stage);
            w->show();
            m_windows << w;
        }
    }

    m_windows.erase(m_windows.begin() + i, m_windows.end());
}
