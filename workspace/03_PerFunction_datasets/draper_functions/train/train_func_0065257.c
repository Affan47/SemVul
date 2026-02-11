kdisplaySetFont()
{
#if !defined(Q_WS_MAEMO_5) && !defined(Q_OS_WINCE) && !defined(MEEGO_EDITION_HARMATTAN)
    if (!kdeFullSession) {
        return;
    }

    if (qApp->type() == QApplication::GuiClient) {
        KGlobalSettingsData* data = KGlobalSettingsData::self();

        QApplication::setFont( data->font(KGlobalSettingsData::GeneralFont) );
        const QFont menuFont = data->font( KGlobalSettingsData::MenuFont );
        QApplication::setFont( menuFont, "QMenuBar" );
        QApplication::setFont( menuFont, "QMenu" );
        QApplication::setFont( menuFont, "KPopupTitle" );
        QApplication::setFont( data->font(KGlobalSettingsData::ToolbarFont), "QToolBar" );
    }
    emit q->kdisplayFontChanged();
    emit q->appearanceChanged();
#endif
}
