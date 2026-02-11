editPreferences()
{
   PreferencesEditorDialog preferences;
   preferences.exec();
   m_Widget.m_pConnections->setFocus();
}
