sorryWId(WId parent_id, const QString &text,
                   const QString &caption, Options options)
{
    QWidget* parent = QWidget::find( parent_id );
    KDialog *dialog = new KDialog(parent, Qt::Dialog);
    dialog->setCaption( caption.isEmpty() ? i18n("Sorry") : caption );
    dialog->setButtons( KDialog::Ok );
    dialog->setObjectName( "sorry" );
    dialog->setDefaultButton( KDialog::Ok );
    dialog->setEscapeButton( KDialog::Ok );
    applyOptions( dialog, options );
    if ( options & KMessageBox::PlainCaption ) {
        dialog->setPlainCaption( caption );
    }
    if ( parent == NULL && parent_id ) {
        KWindowSystem::setMainWindow( dialog, parent_id );
    }

    createKMessageBox(dialog, QMessageBox::Warning, text, QStringList(), QString(), 0, options);
}
