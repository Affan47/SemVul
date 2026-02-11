accept()
{
    if (!d->ui.errorMessage->isHidden()) d->ui.errorMessage->setText( QString() );


    if (!d->ui.passwordLabel->isHidden()) {
        d->ui.passwordLabel->setFont( font() );
        d->ui.userNameLabel->setFont( font() );
    }


    QTimer::singleShot( 0, this, SLOT(actuallyAccept()) );
}
