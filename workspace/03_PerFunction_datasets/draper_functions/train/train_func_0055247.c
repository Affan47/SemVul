RemoveBackupFile()
{
   if(backup_file)
   {
      remove(backup_file);
      backup_file.set(0);
   }
}
