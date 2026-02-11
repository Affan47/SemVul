enableMessage(const QString &dontShowAgainName)
{
   KConfig *config = KMessageBox_againConfig ? KMessageBox_againConfig : KGlobal::config().data();
   if (!config->hasGroup("Notification Messages")) {
      return;
   }

   KConfigGroup cg( config, "Notification Messages" );

   cg.deleteEntry(dontShowAgainName);
   config->sync();
}
