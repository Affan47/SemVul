preferencesActionX()
{
  Preferences preferences(0, formatList, bd);
  preferences.exec();


  setWidgetValues();
}
