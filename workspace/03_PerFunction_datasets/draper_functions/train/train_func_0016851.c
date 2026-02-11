consolePurgeFiles()
{
   if (QMessageBox::warning(this, "Bat",
      tr("Are you sure you want to purge ??  !!!.\n"
"The Purge command will delete associated Catalog database records from Jobs and"
" Volumes without considering the retention period. Purge  works only on the"
" Catalog database and does not affect data written to Volumes. This command can"
" be dangerous because you can delete catalog records associated with current"
" backups of files, and we recommend that you do not use it unless you know what"
" you are doing.\n"
      "Press OK to proceed with the purge operation?"),
      QMessageBox::Ok | QMessageBox::Cancel)
      == QMessageBox::Cancel) { return; }

   m_console->m_warningPrevent = true;
   foreach(QString job, m_selectedJobsList) {
      QString cmd("purge files jobid=");
      cmd += job;
      consoleCommand(cmd, false);
   }
   m_console->m_warningPrevent = false;
   populateTable();
}
