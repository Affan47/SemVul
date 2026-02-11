get_ActionName(bool past)
{
   switch(m_JobType) {
   case JT_BACKUP:
      return _("backup");
   case JT_VERIFY:
      return (past == true) ? _("verified") : _("verify");
   case JT_RESTORE:
      return (past == true) ? _("restored") : _("restore");
   case JT_ARCHIVE:
      return (past == true) ? _("archived") : _("archive");
   case JT_COPY:
      return (past == true) ? _("copied") : _("copy");
   case JT_MIGRATE:
      return (past == true) ? _("migrated") : _("migrate");
   case JT_SCAN:
      return (past == true) ? _("scanned") : _("scan");
   default:
      return _("unknown action");
   }
}
