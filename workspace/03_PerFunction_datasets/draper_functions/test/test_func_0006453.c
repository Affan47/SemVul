set_preferences_manager_show_filebrowser(PreferencesManager *preferences_manager, gboolean newstate)
{
  if (!OBJECT_IS_PREFERENCES_MANAGER (preferences_manager)) return ;
  PreferencesManagerDetails *prefdet;
  prefdet = PREFERENCES_MANAGER_GET_PRIVATE(preferences_manager);
  prefdet->showfilebrowser = newstate;

}
