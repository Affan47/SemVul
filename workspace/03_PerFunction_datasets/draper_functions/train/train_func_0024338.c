verifiedAccount( bool verified, bool  )
{
    if ( verified )

        m_loginWidget->save( false );
    else
        m_loginWidget->resetWidget( The::settings().currentUsername() );

    LastFmUserSettings& user = The::settings().currentUser();
    int iconIndex = ui_account.colourCombo->currentIndex() >= 0 ? ui_account.colourCombo->currentIndex() : 0;
    user.setIcon( static_cast<MooseEnums::UserIconColour>( iconIndex ) );

    The::settings().setShowTrayIcon( ui_account.showInTrayCheck->isChecked() );

#ifdef Q_WS_MAC
    if (appHasDockIcon() != ui_account.showInDockCheck->isChecked())
    {
        QProcess p;
        p.start( "defaults", QStringList() << "write"
                                           << Moose::bundleDirPath() + "/Contents/Info"
                                           << "LSUIElement"
                                           << (ui_account.showInDockCheck->isChecked() ? "0" : "1") );
        p.waitForFinished();

        p.start( "touch", QStringList() << Moose::bundleDirPath() );

        LastMessageBox::say( tr("You need to restart the application for the dock icon appearance change to take effect.") );
    }
#endif

#ifndef HIDE_RADIO

    int langIdx = ui_account.languageCombo->currentIndex();
    QString langCode = ui_account.languageCombo->itemData( langIdx ).toString();
    QString oldLang = The::settings().customAppLanguage();

    if ( langCode != oldLang )
    {
        LastMessageBox dlg( QMessageBox::Information,
            tr( "Restart needed" ),
            tr( "You need to restart the application for the language "
            "change to take effect." ),
            QMessageBox::Ok, this );
        dlg.exec();
    }

    The::settings().setAppLanguage( langCode );
#endif

    if( !verified )
    {

        return;
    }
    else
    {
        if ( m_loginWidget->detailsChanged() )
            m_reconnect = true;
    }

    pageSaved( 0 );

    if ( m_closeAfterVerification )
        accept();
}
