topLevelWindow(QObject* obj)
{
    QWebPage *page = qobject_cast<QWebPage*>(obj);
    QWidget* widget = (page ? page->view() : qobject_cast<QWidget*>(page));
    while (widget && widget->parentWidget()) {
        widget = widget->parentWidget();
    }
    return (widget ? widget->window() : 0);
}
