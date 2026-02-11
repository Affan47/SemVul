saveSettings(QSettings &settings)
{
  saveOptions(settings, name+".input", inputOptions);
  saveOptions(settings, name+".output", outputOptions);
  settings.setValue(name + ".readcount", getReadUseCount());
  settings.setValue(name + ".writecount", getWriteUseCount());
  settings.setValue(name+".hidden", isHidden());
}
