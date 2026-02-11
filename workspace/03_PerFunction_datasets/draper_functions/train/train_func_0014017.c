changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        d->retranslate();
        break;
    default:
        break;
    }
    QWidget::changeEvent(e);
}
