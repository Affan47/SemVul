keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && m_webView) {
        setText(QString::fromUtf8(m_webView->url().toEncoded()));
        selectAll();
        return;
    }

    QString currentText = text().trimmed();
    if ((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        && !currentText.startsWith(QLatin1String("http://"), Qt::CaseInsensitive)) {
        QString append;
        if (event->modifiers() == Qt::ControlModifier)
            append = QLatin1String(".com");
        else if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier))
            append = QLatin1String(".org");
        else if (event->modifiers() == Qt::ShiftModifier)
            append = QLatin1String(".net");
        QUrl url(QLatin1String("http://") + currentText);
        QString host = url.host();
        if (!host.endsWith(append, Qt::CaseInsensitive)) {
            host += append;
            url.setHost(host);
            setText(url.toString());
        }
    }

    LineEdit::keyPressEvent(event);
}
