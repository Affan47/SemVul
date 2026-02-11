preferencesClicked()
{
	Preferences preferences;
	PreferencesDialog dialog(preferences, this);
	if (dialog.exec() == QDialog::Accepted) {
		loadPreferences(preferences);
	}
}
