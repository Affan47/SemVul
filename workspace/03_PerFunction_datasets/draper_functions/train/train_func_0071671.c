closeEvent( QCloseEvent *event )
{
    Q_D(KDialog);
    KPushButton *button = this->button(d->mEscapeButton);
    if (button && !isHidden()) {
        button->animateClick();

        if (testAttribute(Qt::WA_DeleteOnClose)) {

            d->mDeferredDelete = true;
            setAttribute(Qt::WA_DeleteOnClose, false);
        }
    } else {
        QDialog::closeEvent(event);
    }
}
