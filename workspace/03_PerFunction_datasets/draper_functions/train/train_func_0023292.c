createRefreshModelButton()
{
    QToolButton *but = new QToolButton(this);
    aForceModelRefresh = new QAction(this);
    const QString &icon = theme()->iconFileName(CalendarTheme::NavigationForceModelRefreshing);
    if (!icon.isEmpty())
        aForceModelRefresh->setIcon(QIcon(icon));
    but->addAction(aForceModelRefresh);
    but->setDefaultAction(aForceModelRefresh);
    connect(aForceModelRefresh, SIGNAL(triggered()), this, SLOT(refreshModel()));
    return but;
}
