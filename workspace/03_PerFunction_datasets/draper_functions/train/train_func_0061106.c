writeSettings()
{
   QFont font = get_font();

   QSettings settings(m_dir->name(), "bat");
   settings.beginGroup("Console");
   settings.setValue("consoleFont", font.family());
   settings.setValue("consolePointSize", font.pointSize());
   settings.setValue("consoleFixedPitch", font.fixedPitch());
   settings.endGroup();
}
