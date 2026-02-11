PrintDB()

{
switch (TODO)
   {
   case cf_db_lastseen:
       ShowLastSeen();
       break;
   case cf_db_locks:
       ShowLocks(CF_INACTIVE);
       break;
   case cf_db_active:
       ShowLocks(CF_ACTIVE);
       break;
   case cf_db_checksum:
       ShowChecksums();
       break;
   case cf_db_performance:
       ShowPerformance();
       break;
   case cf_db_audit:
       ShowCurrentAudit();
       break;
   case cf_db_classes:
       ShowClasses();
       break;
   default:
       break;
   }
}
