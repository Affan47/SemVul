windowCloseButtonClicked()
{
    qDebug() << Q_FUNC_INFO;
    this->hide();

    Q_EMIT closed(this);
}
