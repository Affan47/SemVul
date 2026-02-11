questionYesNoCancelWId(WId parent_id,
                          const QString &text,
                          const QString &caption,
                          const KGuiItem &buttonYes_,
                          const KGuiItem &buttonNo_,
                          const KGuiItem &buttonCancel_,
                          const QString &dontAskAgainName,
                          Options options)
{
    ButtonCode res;
    if ( !shouldBeShownYesNo(dontAskAgainName, res) ) {
        return res;
    }

    I18N_FILTER_BUTTON_YES(buttonYes_, buttonYes)
    I18N_FILTER_BUTTON_NO(buttonNo_, buttonNo)
    I18N_FILTER_BUTTON_CANCEL(buttonCancel_, buttonCancel)
    I18N_POST_BUTTON_FILTER

    QWidget* parent = QWidget::find( parent_id );
    KDialog *dialog= new KDialog(parent, Qt::Dialog);
    dialog->setCaption( caption.isEmpty() ? i18n("Question") : caption );
    dialog->setButtons( KDialog::Yes | KDialog::No | KDialog::Cancel );
    dialog->setObjectName( "questionYesNoCancel" );
    dialog->setButtonGuiItem( KDialog::Yes, buttonYes );
    dialog->setButtonGuiItem( KDialog::No, buttonNo );
    dialog->setButtonGuiItem( KDialog::Cancel, buttonCancel );
    dialog->setDefaultButton( KDialog::Yes );
    applyOptions( dialog, options );
    if ( options & KMessageBox::PlainCaption ) {
        dialog->setPlainCaption( caption );
    }
    if ( parent == NULL && parent_id ) {
        KWindowSystem::setMainWindow( dialog, parent_id );
    }

    bool checkboxResult = false;
    const int result = createKMessageBox(dialog, QMessageBox::Information,
                       text, QStringList(),
                       dontAskAgainName.isEmpty() ? QString() : i18n("Do not ask again"),
                       &checkboxResult, options);

    if ( result == KDialog::Yes ) {
        res = Yes;
    } else if ( result == KDialog::No ) {
        res = No;
    } else {
        return Cancel;
    }

    if (checkboxResult) {
        saveDontShowAgainYesNo(dontAskAgainName, res);
    }
    return res;
}
