logUserTasks(void) const
{
  ArSyncTask *proc;
  if (mySyncTaskRoot == NULL)
    return;

  proc = mySyncTaskRoot->findNonRecursive("User Tasks");
  if (proc == NULL)
    return;

  proc->log();
}
