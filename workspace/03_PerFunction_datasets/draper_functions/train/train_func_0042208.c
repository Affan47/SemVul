checkAndGetPassword(QString *pwd)
{
    pwd->clear();
    if ( d->ui.linePassword->text() != d->ui.lineVerifyPassword->text() ) {
        d->ui.labelMatch->setPixmap( KTitleWidget::ErrorMessage );
        d->ui.labelMatch->setText( i18n("You entered two different "
                "passwords. Please try again.") );

        d->ui.linePassword->clear();
        d->ui.lineVerifyPassword->clear();
        return false;
    }
    if (d->ui.strengthBar && d->ui.strengthBar->value() < d->passwordStrengthWarningLevel) {
        int retVal = KMessageBox::warningYesNo(this,
                i18n(   "The password you have entered has a low strength. "
                        "To improve the strength of "
                        "the password, try:\n"
                        " - using a longer password;\n"
                        " - using a mixture of upper- and lower-case letters;\n"
                        " - using numbers or symbols as well as letters.\n"
                        "\n"
                        "Would you like to use this password anyway?"),
                i18n("Low Password Strength"));
        if (retVal == KMessageBox::No) return false;
    }
    if ( !checkPassword(d->ui.linePassword->text()) ) {
        return false;
    }

    *pwd = d->ui.linePassword->text();
    return true;
}
