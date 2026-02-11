changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    if (e->type() == QEvent::PaletteChange) {
        d->textLabel->setStyleSheet(d->textStyleSheet());
        d->commentLabel->setStyleSheet(d->commentStyleSheet());
    }
}
