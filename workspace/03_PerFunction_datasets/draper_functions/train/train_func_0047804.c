addWebAction(QAction *action, QWebPage::WebAction webAction)
{
    if (!action)
        return;
    m_actions.append(new WebActionMapper(action, webAction, this));
}
