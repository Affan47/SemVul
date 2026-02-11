qmonReadPreferences(void)
{
   DENTER(TOP_LAYER, "qmonReadPreferences");

   qmon_preferences = cull_read_in_pref(XmtGetHomeDir(), ".qmon_preferences",
                                        0, 0, NULL);
   DEXIT;
}
