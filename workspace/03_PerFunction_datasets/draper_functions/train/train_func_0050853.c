showPreferences()
{
    Qt4GuiPrefs::PreferencesDialog* prefsDialog = new Qt4GuiPrefs::PreferencesDialog(_drawingWidget);

    prefsDialog->setAttribute(Qt::WA_DeleteOnClose);
    prefsDialog->show();
    prefsDialog->raise();
    prefsDialog->activateWindow();
}
