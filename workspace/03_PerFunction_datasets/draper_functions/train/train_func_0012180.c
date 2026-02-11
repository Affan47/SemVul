showMessage(const QString &message, int duration_ms, const QString &css)
{
    LOG(message);
    if (d->m_MessageLabel) {
        delete d->m_MessageLabel;
        d->m_MessageLabel = 0;
    }
    d->m_MessageLabel = new QLabel(this);
    d->m_MessageLabel->setText(message);
    d->m_MessageLabel->setStyleSheet(QString("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %1, stop: 1 %2);")
                                     .arg(this->palette().base().color().lighter(100).name())
                                     .arg(this->palette().base().color().lighter(120).name()));
    if (!css.isEmpty())
        d->m_MessageLabel->setStyleSheet(css);
    d->m_MessageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->m_MessageLabel->adjustSize();

    QPoint topRight = rect().topRight();
    QSize size = d->m_MessageLabel->rect().size();
    QRect rect(topRight.x() - d->m_MessageLabel->rect().width(), topRight.y() + 2, size.width(), size.height());
    d->m_MessageLabel->setGeometry(rect);
    d->m_MessageLabel->show();
    d->m_MessageLabel->raise();
    QTimer::singleShot(duration_ms, d->m_MessageLabel, SLOT(deleteLater()));
}
